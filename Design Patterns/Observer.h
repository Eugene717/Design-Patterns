#pragma once
#include <iostream>
#include <string>
#include <list>

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void Update(const std::string& message_from_subject) = 0;
};

class ISubject
{
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

class Subjecto : public ISubject
{
	std::list<IObserver*> m_list_observer;
	std::string m_message;
public:
	virtual ~Subjecto() {
		std::cout << "Goodbye, I was the Subject.\n";
	}
	void Attach(IObserver* observer) override {
		m_list_observer.push_back(observer);
	}
	void Detach(IObserver* observer) override {
		m_list_observer.remove(observer);
	}
	void Notify() override {
		std::list<IObserver*>::iterator iterator = m_list_observer.begin();
		HowManyObserver();
		while (iterator != m_list_observer.end())
		{
			(*iterator)->Update(m_message);
			++iterator;
		}
	}
	void CreateMessage(std::string message = "Empty") {
		this->m_message = message;
		Notify();		
	}
	void HowManyObserver() {
		std::cout << "There are " << m_list_observer.size() << " observers in the list.\n";
	}
	void SomeBusinessLogic() {
		this->m_message = "change message message";
		Notify();
		std::cout << "I'm about to do some thing important\n";
	}
};

class Observer : public IObserver
{
	std::string m_message_from_subject;
	Subjecto& m_subject;
	static int m_static_number;
	int m_number;
public:
	Observer(Subjecto& subject) : m_subject(subject) {
		this->m_subject.Attach(this);
		std::cout << "Hi, I'm the Observer \"" << ++Observer::m_static_number << "\".\n";
		this->m_number = Observer::m_static_number;
	}
	virtual ~Observer() {
		std::cout << "Goodbye, I was the Observer \"" << this->m_number << "\".\n";
	}
	void Update(const std::string& message_from_subject) override {
		m_message_from_subject = message_from_subject;
		PrintInfo();
	}
	void RemoveMeFromTheList() {
		m_subject.Detach(this);
		std::cout << "Observer \"" << m_number << "\" removed from the list.\n";
	}
	void PrintInfo() {
		std::cout << "Observer \"" << this->m_number << "\": a new message is available --> " << this->m_message_from_subject << "\n";
	}
};

int Observer::m_static_number = 0;

void ClientCode5()
{
	Subjecto* subject = new Subjecto;
	Observer* observer1 = new Observer(*subject);
	Observer* observer2 = new Observer(*subject);
	Observer* observer3 = new Observer(*subject);
	Observer* observer4;
	Observer* observer5;

	subject->CreateMessage("Hello World!");
	observer3->RemoveMeFromTheList();

	subject->CreateMessage("The weather is hot today!");
	observer4 = new Observer(*subject);

	observer2->RemoveMeFromTheList();
	observer5 = new Observer(*subject);

	subject->CreateMessage("My new car is great!");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete subject;
}

void foo18()
{
	ClientCode5();
}
