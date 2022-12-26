#pragma once
#include <iostream>
#include <string>

class Handler
{
public:
	virtual Handler* SetNext(Handler* handler) = 0;
	virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler
{
	Handler* m_next_handler;
public:
	AbstractHandler() : m_next_handler(nullptr) {}
	Handler* SetNext(Handler* handler) override {
		this->m_next_handler = handler;
		return handler;
	}
	std::string Handle(std::string request) override {
		if (this->m_next_handler)
			return this->m_next_handler->Handle(request);
		return {};
	}
};

class MonkeyHandler : public AbstractHandler
{
public:
	std::string Handle(std::string request) override {
		if (request == "Banana")
			return "Monkey: I'll eat the " + request + ".\n";
		else
			return AbstractHandler::Handle(request);
	}
};

class SquirrelHandler : public AbstractHandler
{
public:
	std::string Handle(std::string request) override {
		if (request == "Nut")
			return "Squirrel: I'll eat the " + request + ".\n";
		else
			return AbstractHandler::Handle(request);
	}
};

class DogHandler : public AbstractHandler
{
public:
	std::string Handle(std::string request) override {
		if (request == "MeatBall")
			return "Dog: I'll eat the " + request + ".\n";
		else
			return AbstractHandler::Handle(request);
	}
};


void ClientCode(Handler& handler)
{
	std::vector<std::string> food = { "Nut", "Banana", "Cup of coffee" };
	for (const std::string& f : food)
	{
		std::cout << "Client: Who wants a " << f << "?\n";
		const std::string result = handler.Handle(f);
		if (!result.empty())
			std::cout << "  " << result;
		else
			std::cout << "  " << f << " was left untouched.\n";
	}
}

void foo13()
{
	MonkeyHandler* monkey = new MonkeyHandler;
	SquirrelHandler* squirrel = new SquirrelHandler;
	DogHandler* dog = new DogHandler;
	monkey->SetNext(squirrel)->SetNext(dog);

	std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
	ClientCode(*monkey);
	std::cout << "\n";
	std::cout << "Subchain: Squirrel > Dog\n\n";
	ClientCode(*squirrel);

	delete monkey;
	delete squirrel;
	delete dog;
}
