#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

enum Type
{
	PROTOTYPE_1 = 0,
	PROTOTYPE_2
};

class Prototype
{
protected:
	std::string m_prototype_name;
	float m_prototype_field;
public:
	Prototype() {}
	Prototype(std::string prototype_name) : m_prototype_name(prototype_name) {}
	virtual ~Prototype() {}
	virtual Prototype* Clone() const = 0;
	virtual void Method(float prototype_field)	{
		m_prototype_field = prototype_field;
		std::cout << "Call Method from " << m_prototype_name << " with field : " << m_prototype_field;
	}
};

class ConcretePrototype1 : public Prototype
{
	float m_concrete_prototype_field1;
public:
	ConcretePrototype1(std::string prototype_name, float concrete_prototype_field) : Prototype(prototype_name), m_concrete_prototype_field1(concrete_prototype_field) {}
	Prototype* Clone() const override {
		return new ConcretePrototype1(*this);
	}
};

class ConcretePrototype2 : public Prototype
{
	float m_concrete_prototype_field2;
public:
	ConcretePrototype2(std::string prototype_name, float concrete_prototype_field) : Prototype(prototype_name), m_concrete_prototype_field2(concrete_prototype_field) {}
	Prototype* Clone() const override {
		return new ConcretePrototype2(*this);
	}
};

class PrototypeFactory
{
	std::unordered_map<Type, Prototype*, std::hash<int>> m_prototypes;
public:
	PrototypeFactory() {
		m_prototypes[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 50.f);
		m_prototypes[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2", 60.f);
	}
	~PrototypeFactory() {
		delete m_prototypes[Type::PROTOTYPE_1];
		delete m_prototypes[Type::PROTOTYPE_2];
	}

	Prototype* CreatePrototype(Type type) {
		return m_prototypes[type]->Clone();
	}
};


void Client(PrototypeFactory& prototype_factory)
{
	std::cout << "Let's create a Prototype 1\n";

	Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
	prototype->Method(90);
	delete prototype;

	std::cout << "\n";
	std::cout << "Let's create a Prototype 2\n";

	prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
	prototype->Method(10);
	delete prototype;
}


void foo5()
{
	PrototypeFactory * prototype_factory = new PrototypeFactory();
	Client(*prototype_factory);
}
