#pragma once
#include <iostream>
#include <string>
#include <time.h>

class Memento
{
public:
	virtual ~Memento() {}
	virtual std::string GetName() const = 0;
	virtual std::string date() const = 0;
	virtual std::string state() const = 0;
};

class ConcreteMemento : public Memento
{
	std::string m_state;
	std::string m_date;
public:
	ConcreteMemento(std::string state) {
		this->m_state = state;
		std::time_t now = std::time(0);
		this->m_date = std::ctime(&now);
	}
	std::string state() const override {
		return this->m_state;
	}
	std::string GetName() const override {
		return this->m_date + " / (" + this->m_state.substr(0, 9) + "...)";
	}
	std::string date() const override {
		return this->m_date;
	}
};

class Originator
{
	std::string m_state;
	std::string GenerateRandomString(int length = 10) {
		const char alphanum[] = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
		int stringLenght = sizeof(alphanum) - 1;

		std::string random_string;
		for (int i = 0; i < length; i++)
		{
			random_string += alphanum[std::rand() % stringLenght];
		}
		return random_string;
	}
public:
	Originator(std::string state) :m_state(state) {
		std::cout << "Originator: My initial state is: " << this->m_state << "\n";
	}
	void DoSomething() {
		std::cout << "Originator: I'm doing something important.\n";
		this->m_state = this->GenerateRandomString(30);
		std::cout << "Originator: and my state has changed to: " << this->m_state << "\n";
	}
	Memento* Save() {
		return new ConcreteMemento(this->m_state);
	}
	void Restore(Memento* memento) {
		this->m_state = memento->state();
		std::cout << "Originator: My state has changed to: " << this->m_state << "\n";
	}
};

class Caretaker
{
	std::vector<Memento*> m_mementos;
	Originator* m_originator;
public:
	Caretaker(Originator* originator) : m_originator(originator) {}
	~Caretaker() {
		for (auto m : m_mementos) delete m;
	}
	void Backup() {
		std::cout << "\nCaretaker: Saving Originator's state...\n";
		this->m_mementos.push_back(this->m_originator->Save());
	}
	void Undo() {
		if (!this->m_mementos.size())
			return;
		Memento* memento = this->m_mementos.back();
		this->m_mementos.pop_back();
		std::cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
		try {
			this->m_originator->Restore(memento);
		}
		catch (...) {
			this->Undo();
		}
	}
	void ShowHistory() const {
		std::cout << "Caretaker: Here's the list of mementos:\n";
		for (Memento* memento : this->m_mementos)
			std::cout << memento->GetName() << "\n";
	}
};


void ClientCode4()
{
	Originator* originator = new Originator("Super-duper-super-puper-super.");
	Caretaker* caretaker = new Caretaker(originator);
	caretaker->Backup();
	originator->DoSomething();
	caretaker->Backup();
	originator->DoSomething();
	caretaker->Backup();
	originator->DoSomething();
	std::cout << "\n";
	caretaker->ShowHistory();
	std::cout << "\nClient: Now, let's rollback!\n\n";
	caretaker->Undo();
	std::cout << "\nClient: Once more!\n\n";
	caretaker->Undo();

	delete originator;
	delete caretaker;
}

void foo17()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	ClientCode4();
}
