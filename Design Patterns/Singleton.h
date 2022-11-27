#pragma once

#include <iostream>
#include <string>

class Singleton
{
	static Singleton* m_singleton;

	Singleton() {
		m_str = "Singleton works";
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	std::string m_str;
	static Singleton* GetInstance()	{
		if (m_singleton == nullptr)
			m_singleton = new Singleton();
		return m_singleton;
	}
};

Singleton* Singleton::m_singleton = nullptr;

void foo2()
{
	Singleton* singleton = Singleton::GetInstance();

	std::cout << singleton->m_str << std::endl;
}
