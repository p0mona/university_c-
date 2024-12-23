//Task1

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

using namespace std;

class B {
public:
    virtual ~B() {}
    virtual void operator() (void) = 0;
};

class C : public B {
public:
    virtual ~C() { cout << "C is deleted" << endl; }

    void operator() (void) override {
        cout << "C is doing an action..." << endl;
    }
};

class D : public B {
public:
    virtual ~D() { cout << "D is deleted" << endl; }

    void operator() (void) override {
        cout << "D is doing an action..." << endl;
    }
};

class E : public B {
public:
    virtual ~E() { cout << "E is deleted" << endl; }

    void operator() (void) override {
        cout << "E is doing an action..." << endl;
    }
};

class F : public B {
public:
    virtual ~F() { cout << "F is deleted" << endl; }

    void operator() (void) override {
        cout << "F is doing an action..." << endl;
    }
};

enum class EClassId { kC, kD, kE, kF };

auto Factory(EClassId id) {
    switch (id) {
    case EClassId::kC: return unique_ptr<B>(make_unique<C>());
    case EClassId::kD: return unique_ptr<B>(make_unique<D>());
    case EClassId::kE: return unique_ptr<B>(make_unique<E>());
    case EClassId::kF: return unique_ptr<B>(make_unique<F>());
    default: assert(false);
    }
    return unique_ptr<B>();
}

void FactoryTest(void) {
    vector<unique_ptr<B>> theObjects;
    theObjects.push_back(Factory(EClassId::kC));
    theObjects.emplace_back(Factory(EClassId::kD));
    theObjects.emplace_back(Factory(EClassId::kE));
    theObjects.emplace_back(Factory(EClassId::kF));

    theObjects[theObjects.size() - 1] = Factory(EClassId::kD);

    for (auto& a : theObjects) (*a)();
}

int main() {
    FactoryTest();
    return 0;
}
