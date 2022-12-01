#pragma once
#include <iostream>
#include <vector>

class Product1
{
public:
	std::vector<std::string> m_pieces;
	void ListPieces() const {
		std::cout << "Products pieces: ";
		for (size_t i = 0; i < m_pieces.size(); i++)
			if (m_pieces[i] == m_pieces.back())
			{
				std::cout << m_pieces[i];
			}
			else
			{
				std::cout << m_pieces[i] << ", ";
			}
		std::cout << "\n\n";
	}
};


class Builder
{
public:
	virtual ~Builder() {}
	virtual void ProducePieceA() const = 0;
	virtual void ProducePieceB() const = 0;
	virtual void ProducePieceC() const = 0;
};

class ConcreteBuilder1 : public Builder
{
	Product1* product;
public:
	ConcreteBuilder1()	{
		this->Reset();
	}
	~ConcreteBuilder1() {
		delete product;
	}
	void Reset() {
		this->product = new Product1();
	}

	void ProducePieceA() const override {
		this->product->m_pieces.push_back("PartA1");
	}
	void ProducePieceB() const override {
		this->product->m_pieces.push_back("PartB1");
	}
	void ProducePieceC() const override {
		this->product->m_pieces.push_back("PartC1");
	}
	
	Product1* GetProduct() {
		Product1* result = this->product;
		this->Reset();
		return result;
	}
};

class Director
{
	Builder* builder;
public:
	void set_builder(Builder* builder) {
		this->builder = builder;
	}
	void BuildMinimalViableProduct() {
		this->builder->ProducePieceA();
	}
	void BuildFullFeaturedProduct() {
		this->builder->ProducePieceA();
		this->builder->ProducePieceB();
		this->builder->ProducePieceC();
	}
};

void ClientCode(Director& director)
{
	ConcreteBuilder1* builder = new ConcreteBuilder1();
	director.set_builder(builder);
	std::cout << "Standart basic product:\n";
	director.BuildMinimalViableProduct();

	Product1* p = builder->GetProduct();
	p->ListPieces();
	delete p;

	std::cout << "Standart full featured product:\n";
	director.BuildFullFeaturedProduct();

	p = builder->GetProduct();
	p->ListPieces();
	delete p;

	std::cout << "Custom product:\n";
	builder->ProducePieceA();
	builder->ProducePieceC();
	p = builder->GetProduct();
	p->ListPieces();
	delete p;

	delete builder;
}

void foo4()
{
	Director* director = new Director();
	ClientCode(*director);
	delete director;
}
