#include <iostream>
#include <string>
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

void print_id(AbstractPrototype const &proto, string s="") {
    cout << s << "Prototype ID: " << &proto << endl;
}

int main() {
    // poitner instance
    ConcreteProtoA* proto_a_ptr = new ConcreteProtoA{10};
    print_id(*proto_a_ptr);
    proto_a_ptr->print();
    ConcreteProtoA* proto_a_ptr_clone = proto_a_ptr->clone();
    print_id(*proto_a_ptr_clone, "cloned ");
    proto_a_ptr_clone->print();
    // instance
    ConcreteProtoA proto_a = ConcreteProtoA{100};
    print_id(proto_a);
    proto_a.print();
    // ConcreteProtoA proto_a_clone = proto_a.clone(); // not allowed since a pointer to the clone is returned
    ConcreteProtoA* proto_a_clone = proto_a.clone();
}