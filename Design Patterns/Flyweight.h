#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

struct SharedState
{
	std::string m_brand;
	std::string m_model;
	std::string m_color;

	SharedState(const std::string& brand, const std::string& model, const std::string& color) :m_brand(brand), m_model(model), m_color(color) {}

	friend std::ostream& operator<<(std::ostream& os, const SharedState& ss) {
		return os << "[ " << ss.m_brand << " , " << ss.m_model << " , " << ss.m_color << " ]";
	}
};

struct UniqueState
{
	std::string m_owner;
	std::string m_plates;

	UniqueState(const std::string& owner, const std::string& plates) :m_owner(owner), m_plates(plates) {}

	friend std::ostream& operator<<(std::ostream& os, const UniqueState& us) {
		return os << "[ " << us.m_owner << " , " << us.m_plates << " ]";
	}
};


class Flyweight
{
	SharedState* m_shared_state;
public:
	Flyweight(const SharedState* shared_state) :m_shared_state(new SharedState(*shared_state)) {}
	Flyweight(const Flyweight& other) :m_shared_state(new SharedState(*other.m_shared_state)) {}
	~Flyweight() {
		delete m_shared_state;
	}
	SharedState* shared_state() const {
		return m_shared_state;
	}
	void Operation(const UniqueState& unique_state) const {
		std::cout << "Flyweight: Display shared (" << *m_shared_state << " ) and unique (" << unique_state << ") state.\n";
	}
};


class FlyweightFactory
{
	std::unordered_map<std::string, Flyweight> m_flyweights;
	std::string GetKey(const SharedState& ss) const {
		return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
	}
public:
	FlyweightFactory(std::initializer_list<SharedState> share_states) {
		for (const SharedState& ss : share_states)
		{
			this->m_flyweights.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
		}
	}

	Flyweight GetFlyweight(const SharedState& shared_state) {
		std::string key = this->GetKey(shared_state);
		if (this->m_flyweights.find(key) == this->m_flyweights.end())
		{
			std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
			this->m_flyweights.insert(std::make_pair(key, Flyweight(&shared_state)));
		}
		else
		{
			std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
		}
		return this->m_flyweights.at(key);
	}
	void ListFlyweights() const {
		size_t count = this->m_flyweights.size();
		std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
		for (std::pair<std::string, Flyweight> pair : this->m_flyweights)
		{
			std::cout << pair.first << "\n";
		}
	}
};


void AddCarToPoliceDatabase(FlyweightFactory& ff, const std::string& plates, const std::string& owner, const std::string& brand, const std::string& model, const std::string& color)
{
	std::cout << "\nClient: Adding a car to database.\n";
	const Flyweight& flyweight = ff.GetFlyweight({ brand, model, color });
	flyweight.Operation({ owner, plates });
}

void foo11()
{
	FlyweightFactory* factory = new FlyweightFactory({ {"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"} });
	factory->ListFlyweights();

	AddCarToPoliceDatabase(*factory, "CL234IR",	"James Doe", "BMW",	"M5", "red");
	AddCarToPoliceDatabase(*factory, "CL234IR",	"James Doe", "BMW",	"X1", "red");
	factory->ListFlyweights();
	delete factory;
}
