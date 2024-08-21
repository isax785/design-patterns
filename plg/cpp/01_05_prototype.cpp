#include <iostream>
using namespace std;

class AbstractPrototype {
    public:
        virtual AbstractPrototype* clone() const=0;
        virtual void print() const=0;
        virtual ~AbstractPrototype() = default;
};

class ConcreteProtoA : public AbstractPrototype {
    private:
        int _v;
    public:
        ConcreteProtoA(int v) : _v(v) {};
        virtual ConcreteProtoA* clone() const override
        {
            return new ConcreteProtoA(*this);
        };
        virtual void print() const override {cout << "Prototype A - value: " << _v << endl;};
};

class ConcreteProtoB: public AbstractPrototype {
    private:
        int _v;
    public:
        ConcreteProtoB(int v) : _v(v) {};
        virtual ConcreteProtoB* clone() const override
        {
            return new ConcreteProtoB(*this);
        };
        virtual void print() const override {cout << "Prototype B - value: " << _v << endl;};
};

void print_id(AbstractPrototype const &proto) {
    cout << "Prototype ID: " << &proto << endl;
}

int main() {
    ConcreteProtoA* proto_a_ptr = new ConcreteProtoA{10};
    print_id(*proto_a_ptr);
    proto_a_ptr->print();
    ConcreteProtoA proto_a = ConcreteProtoA{100};
    print_id(proto_a);
    proto_a.print();
}