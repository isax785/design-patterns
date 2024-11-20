#include "dp_includes.h"

struct Beverage {
    
    void prepare_beverage() {
        boil_water();
        brew();
        pour_in_cup();
        add_condiments();
    }
    void boil_water() { cout << "Boiling Water" << endl;}
    void pour_in_cup() { cout << "Pouring Into Cup" << endl;}

    virtual void brew()=0;
    virtual void add_condiments()=0;
};

struct Tea : public Beverage {
    void brew() override { cout << "Steeping the Tea" << endl; }
    void add_condiments() override { cout << "Adding Lemon" << endl; }
};

struct Coffee : public Beverage {
    void brew() override { cout << "Dripping Cofee Through Filter" << endl; }
    void add_condiments() override { cout << "Adding Sugar and Milk" << endl; }
};

void prepare_beverage(Beverage *beverage) { beverage->prepare_beverage(); }

int main() {
    cout << "Preparing Tea ..." << endl;
    Tea tea = Tea();
    prepare_beverage(&tea);
    cout << "Preparing Coffee ..." << endl;
    Coffee coffee = Coffee();
    prepare_beverage(&coffee);
}