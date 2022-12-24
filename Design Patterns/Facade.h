#pragma once
#include <iostream>
#include <string>

class Subsystem1
{
public:
	std::string Operation1() const {
		return "Subsystem1: Ready!\n";
	}
	std::string OperationN() const {
		return "Subsystem1: Go!\n";
	}
};

class Subsystem2
{
public:
	std::string Operation1() const {
		return "Subsystem2: Get Ready!\n";
	}
	std::string OperationZ() const {
		return "Subsystem2: Fire!\n";
	}
};


class Facade
{
protected:
	Subsystem1* m_subsystem1;
	Subsystem2* m_subsystem2;
public:
	Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) {
		this->m_subsystem1 = subsystem1 ? nullptr : new Subsystem1;
		this->m_subsystem2 = subsystem2 ? nullptr : new Subsystem2;
	}
	~Facade() {
		delete m_subsystem1;
		delete m_subsystem2;
	}
	std::string Operation() {
		std::string result = "Facade initializes subsystems:\n";
		result += this->m_subsystem1->Operation1();
		result += this->m_subsystem2->Operation1();
		result += "Facade orders subsystems to perform the action:\n";
		result += this->m_subsystem1->OperationN();
		result += this->m_subsystem2->OperationZ();
		return result;
	}
};


void ClientCode(Facade* facade)
{
	std::cout << facade->Operation();
}

void foo10()
{
	Subsystem1* subsystem1 = new Subsystem1;
	Subsystem2* subsystem2 = new Subsystem2;
	Facade* facade = new Facade(subsystem1, subsystem2);
	ClientCode(facade);

	delete facade;
}
