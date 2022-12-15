#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

class Component
{
protected:
	Component* m_parent;
public:
	virtual ~Component() {}
	void SetParent(Component* parent) {
		this->m_parent = parent;
	}
	Component* GetParent() {
		return this->m_parent;
	}
	virtual void Add(Component* component) {}
	virtual void Remove(Component* component) {}

	virtual bool IsComposite() const {
		return false;
	}
	virtual std::string Operation() const = 0;
};


class Leaf : public Component
{
public:
	std::string Operation() const override {
		return "Leaf";
	}
};


class Composite : public Component
{
protected:
	std::list<Component*> m_children;
public:
	void Add(Component* component) override {
		this->m_children.push_back(component);
		component->SetParent(this);
	}
	void Remove(Component* component) override {
		m_children.remove(component);
		component->SetParent(nullptr);
	}
	bool IsComposite() const override {
		return true;
	}
	std::string Operation() const override {
		std::string result;
		for (const Component* c : m_children)
		{
			if (c == m_children.back())
				result += c->Operation();
			else
				result += c->Operation() + "+";
		}
		return "Branch(" + result + ")";
	}
};


void ClientCode(Component* component)
{
	std::cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component* component1, Component* component2)
{
	if (component1->IsComposite())
		component1->Add(component2);
	std::cout << "RESULT: " << component1->Operation();
}


void foo8()
{
	Component* simple = new Leaf;
	std::cout << "Client: I've got a simple component:\n";
	ClientCode(simple);
	std::cout << "\n\n";

	Component* tree = new Composite;
	Component* branch1 = new Composite;

	Component* leaf_1 = new Leaf;
	Component* leaf_2 = new Leaf;
	Component* leaf_3 = new Leaf;
	branch1->Add(leaf_1);
	branch1->Add(leaf_2);
	Component* branch2 = new Composite;
	branch2->Add(leaf_3);
	tree->Add(branch1);
	tree->Add(branch2);
	std::cout << "Client: Now I've got a composite tree:\n";
	ClientCode(tree);
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	ClientCode2(tree, simple);
	std::cout << "\n";

	delete simple;
	delete tree;
	delete branch1;
	delete branch2;
	delete leaf_1;
	delete leaf_2;
	delete leaf_3;
}
