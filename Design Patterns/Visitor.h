#pragma once
#include <iostream>
#include <string>
#include <array>

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};

class ComponentV {
public:
    virtual ~ComponentV() {}
    virtual void Accept(Visitor* visitor) const = 0;
};

class ConcreteComponentA : public ComponentV {
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
    std::string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class ConcreteComponentB : public ComponentV {
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
    std::string SpecialMethodOfConcreteComponentB() const {
        return "B";
    }
};

class ConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};


void ClientCode(std::array<const ComponentV*, 2> components, Visitor* visitor) {
    for (const ComponentV* comp : components) {
        comp->Accept(visitor);
    }
}

void foo22() {
    std::array<const ComponentV*, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const ComponentV* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;
}