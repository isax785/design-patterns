#include <iostream>
#include <string>
using namespace std;

/*
// example:
struct Vehicle {
    virtual string drive() const =0;
    virtual string* drive_two()=0;
    virtual ~Vehicle() {};
};

struct Car: public Vehicle {
    string drive() const override {return "CAR is driving";};
    string* drive_two() override {
        string s = "CAR TWO is driving";
        return &s;
        };
};
*/

class Parent {
    virtual string pure_virtual() = 0;
    virtual string* pure_virtual_ptr()=0;
    virtual string& pure_virtual_ref()=0;
    // the funcitons below are not defined
    virtual string virt();
    virtual string* virt_ptr();
    virtual string& virt_ref();
};

class Child : Parent {

};

class ChildPartial : Parent {
    // defines only some of the Parent methods
    // check which ones can be undefined
    public:
        string pure_virtual() override {return "pure_virtual overridden!";};
};

struct ParentStruct {

};

class ChildStruct : ParentStruct {

};

int main() {
    return 0;
}