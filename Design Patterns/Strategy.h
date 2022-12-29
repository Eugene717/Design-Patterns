#pragma once
#include <iostream>
#include <string>

class Strategy
{
public:
	virtual ~Strategy() = default;
	virtual std::string doAlgorithm(std::string_view data) const = 0;
};

class Contexts
{
	std::unique_ptr<Strategy> m_strategy;
public:
	explicit Contexts(std::unique_ptr<Strategy>&& strategy = {}) : m_strategy(std::move(strategy)) {}
	void set_strategy(std::unique_ptr<Strategy>&& strategy)	{
		m_strategy = std::move(strategy);
	}
	void doSomeBusinessLogic() const {
		if (m_strategy) {
			std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
			std::string result = m_strategy->doAlgorithm("aecbd");
			std::cout << result << "\n";
		}
		else
			std::cout << "Context: Strategy isn't set\n";
	}
};

class ConcreteStrategyA : public Strategy
{
public:
	std::string doAlgorithm(std::string_view data) const override {
		std::string result(data);
		std::sort(std::begin(result), std::end(result));
		return result;
	}
};

class ConcreteStrategyB : public Strategy
{
	std::string doAlgorithm(std::string_view data) const override {
		std::string result(data);
		std::sort(std::begin(result), std::end(result), std::greater<>());
		return result;
	}
};

void ClientCode7()
{
	Contexts context(std::make_unique<ConcreteStrategyA>());
	std::cout << "Client: Strategy is set to normal sorting.\n";
	context.doSomeBusinessLogic();
	std::cout << "\n";
	std::cout << "Client: Strategy is set to reverse sorting.\n";
	context.set_strategy(std::make_unique<ConcreteStrategyB>());
	context.doSomeBusinessLogic();
}

void foo20()
{
	ClientCode7();
}
