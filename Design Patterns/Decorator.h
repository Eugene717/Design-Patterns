#pragma once
#include <iostream>
#include <string>

class Component_d
{
public:
	virtual ~Component_d() {}
	virtual std::string Operation() const = 0;
};

class ConcreteComponent : public Component_d
{
public:
	std::string Operation() const override {
		return "ConcreteComponent";
	}
};


class Decorator : public Component_d
{
protected:
	Component_d* m_component;
public:
	Decorator(Component_d* component) : m_component(component) {}
	std::string Operation() const override {
		return this->m_component->Operation();
	}
};

class ConcreteDecoratorA : public Decorator
{
public:
	ConcreteDecoratorA(Component_d* component) : Decorator(component) {}
	std::string Operation() const override {
		return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
	}
};

class ConcreteDecoratorB : public Decorator
{
public:
	ConcreteDecoratorB(Component_d* component) :Decorator(component) {}
	std::string Operation() const override {
		return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
	}
};


void ClientCode(Component_d* component)
{
	std::cout << "Result: " << component->Operation();
}

void foo9()
{
	Component_d* simple = new ConcreteComponent;
	std::cout << "Client: I've got a simple component:\n";
	ClientCode(simple);
	std::cout << "\n\n";

	Component_d* decorator1 = new ConcreteDecoratorA(simple);
	Component_d* decorator2 = new ConcreteDecoratorB(decorator1);
	std::cout << "Client: Now I've got a decorator component:\n";
	ClientCode(decorator2);
	std::cout << "\n";

	delete simple;
	delete decorator1;
	delete decorator2;
}
