#include <iostream>

using namespace std;

// Pure virtual function declaration:
//      virtual void f() = 0;
// Non-pure virtual function override
//      void f() override {// code here};
// Override to pure virtual
//      void g() override = 0;

struct Abstract
{
    virtual void f() = 0;  // pure virtual
    virtual void g();      // non-pure virtual
}; // "Abstract" is abstract
 
struct Concrete : Abstract
{
    void f() override {cout << "Concrete f()" << endl;}   // non-pure virtual
    // virtual void g();      // non-pure virtual
    void g() {cout << "Concrete g()" << endl;}
    void h() {cout << "Concrete h()" << endl;}
    // virtual void i() = 0;
}; // "Concrete" is non-abstract
 
struct Abstract2 : Concrete
{
    virtual void h() = 0;
    void g() override = 0; // pure virtual overrider
}; // "Abstract2" is abstract
 
int main()
{
    // Abstract a;   // Error: abstract class
    Concrete b;      // OK
    cout << typeid(b).name() << endl;
    b.f();
    b.g();
    b.h();
    Abstract& a = b; // OK to reference abstract base
    cout << typeid(a).name() << endl;
    a.f();           // virtual dispatch to Concrete::f()
    a.g();
    // Abstract2 a2; // Error: abstract class (final overrider of g() is pure)
    Abstract* p = &b; // OK to poin to the instnce with the abstract parent type
    cout << typeid(p).name() << endl;
    cout << "Is p a pointer? " << typeid(p).__is_pointer_p() << endl;
}