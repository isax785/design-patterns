#include <iostream>

class Prototype {
    virtual int clone()=0;
};

class ToBeCloned {};

class ConcretePrototype: Prototype {
    private:
        int _value;
    public:
        int clone() override {return 0;};
};

int main() {

}