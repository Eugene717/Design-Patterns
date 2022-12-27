#pragma once
#include <iostream>
#include <string>

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute() const = 0;
};

class SimpleCommand : public Command
{
	std::string m_pay_load;
public:
	explicit SimpleCommand(std::string pay_load) : m_pay_load(pay_load) {}
	void Execute() const override {
		std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->m_pay_load << ")\n";
	}
};

class Receiver
{
public:
	void DoSomething(const std::string& a)	{
		std::cout << "Receiver: Working on (" << a << ".)\n";
	}
	void DoSomethingElse(const std::string& b) {
		std::cout << "Receiver: Also working on (" << b << ".)\n";
	}
};

class ComplexCommand : public Command
{
	Receiver* m_receiver;

	std::string m_a;
	std::string m_b;
public:
	ComplexCommand(Receiver* receiver, std::string a, std::string b) : m_receiver(receiver), m_a(a), m_b(b) {}
	void Execute() const override {
		std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
		this->m_receiver->DoSomething(this->m_a);
		this->m_receiver->DoSomethingElse(this->m_b);
	}
};

class Invoker
{
	Command* m_on_start;
	Command* m_on_finish;
public:
	~Invoker() {
		delete m_on_start;
		delete m_on_finish;
	}
	void SetOnStart(Command* command) {
		this->m_on_start = command;
	}
	void SetOnFinish(Command* command) {
		this->m_on_finish = command;
	}
	void DoSomethingImportant() {
		std::cout << "Invoker: Does anybody want something done before I begin?\n";
		if (this->m_on_start)
			this->m_on_start->Execute();

		std::cout << "Invoker: ...doing something really important...\n";
		std::cout << "Invoker: Does anybody want something done after I finish?\n";

		if (this->m_on_finish)
			this->m_on_finish->Execute();
	}
};


void foo14()
{
	Invoker* invoker = new Invoker;
	invoker->SetOnStart(new SimpleCommand("Say Hi!"));
	Receiver* receiver = new Receiver;
	invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
	invoker->DoSomethingImportant();

	delete invoker;
	delete receiver;
}
