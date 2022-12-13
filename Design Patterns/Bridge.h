#pragma once
#include <iostream>

struct RealizationIMPL;

struct RealizationIMPL       //all realization in cpp file
{
	int a;
	int b;
	RealizationIMPL(int a) : a(a), b(5) {}
};

class Abstraction
{
	RealizationIMPL* m_pImpl;
public:
	Abstraction(int a) {
		m_pImpl = new RealizationIMPL(a);
	}
	void Activate() { std::cout << m_pImpl->a << '\t' << m_pImpl->b << '\n'; }
};

void foo7()
{
	Abstraction abstraction(3);

	abstraction.Activate();
}
