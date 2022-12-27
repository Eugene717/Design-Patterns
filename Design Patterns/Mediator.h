#pragma once
#include <iostream>
#include <string>

class BaseComponent;
class Mediator
{
public:
	virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};

class BaseComponent
{
protected:
	Mediator* m_mediator;
public:
	BaseComponent(Mediator* mediator = nullptr) : m_mediator(mediator) {}
	void SetMediator(Mediator* mediator) {
		this->m_mediator = mediator;
	}
};

class Component1 :public BaseComponent
{
public:
	void DoA() {
		std::cout << "Component 1 does A.\n";
		this->m_mediator->Notify(this, "A");
	}
	void DoB() {
		std::cout << "Component 1 does B.\n";
		this->m_mediator->Notify(this, "B");
	}
};

class Component2 : public BaseComponent
{
public:
	void DoC() {
		std::cout << "Component 2 does C.\n";
		this->m_mediator->Notify(this, "C");
	}
	void DoD() {
		std::cout << "Component 2 does D.\n";
		this->m_mediator->Notify(this, "D");
	}
};

class ConcreteMediator : public Mediator
{
	Component1* m_component1;
	Component2* m_component2;
public:
	ConcreteMediator(Component1* c1, Component2* c2) : m_component1(c1), m_component2(c2) {
		this->m_component1->SetMediator(this);
		this->m_component2->SetMediator(this);
	}
	void Notify(BaseComponent* sender, std::string event) const override {
		if (event == "A") 
		{
			std::cout << "Mediator reacts on A and triggers following operations:\n";
			this->m_component2->DoC();
		}
		if (event == "D")
		{
			std::cout << "Mediator reacts on D and triggers following operations:\n";
			this->m_component1->DoB();
			this->m_component2->DoC();
		}
	}
};

void ClientCode3()
{
	Component1* c1 = new Component1;
	Component2* c2 = new Component2;
	ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
	std::cout << "Client triggers operation A.\n";
	c1->DoA();
	std::cout << "\n";
	std::cout << "Client triggers operation D.\n";
	c2->DoD();

	delete c1;
	delete c2;
	delete mediator;
}

void foo16()
{
	ClientCode3();
}
