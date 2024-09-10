#include <iostream>
#include <string>

using namespace std;

struct Coffee {
    virtual int cost()=0;
    virtual string description()=0;
};

struct SimpleCoffee: public Coffee {
    int cost() override {return 5;};
    string description() override {return "Simple Coffee";};
};

struct CoffeeDecorator : public Coffee {
    CoffeeDecorator(Coffee* coffee) : _coffee(coffee) {};
    int cost() override {return _coffee->cost();};
    string description() override {return _coffee->description();};
    Coffee* _coffee;
};

struct MilkDecorator : public CoffeeDecorator {
    MilkDecorator(Coffee *coffee) : CoffeeDecorator(coffee) {};
    int cost() {return _coffee->cost() + 2;}
    string description() {return _coffee->description() + ", Milk";}
};

// This allows redeclaring the variable my_coffee:
//             my_coffee = new MilkDecorator(my_coffee);
// but returns a warning when compiling:
// warning: direct base 'Coffee' inaccessible in 'WipDecorator' due to ambiguity [-Winaccessible-base]

// struct WipDecorator : public Coffee,  public CoffeeDecorator  {
//     WipDecorator(Coffee *coffee) : CoffeeDecorator(coffee) {};
//     int cost() override {return _coffee->cost() + 3;}
//     string description() override {return _coffee->description() + ", Wip";}
// };

struct WipDecorator : public CoffeeDecorator  {
    WipDecorator(Coffee *coffee) : CoffeeDecorator(coffee) {};
    int cost() override {return _coffee->cost() + 3;}
    string description() override {return _coffee->description() + ", Wip";}
};

int main() {
    Coffee* my_coffee = new SimpleCoffee();
    cout << "Description: " << my_coffee->description() << " - cost: " << my_coffee->cost() << endl;
    // now decorating
    CoffeeDecorator * my_coffee_d = new CoffeeDecorator(my_coffee);
    cout << "Description: " << my_coffee_d->description() << " - cost: " << my_coffee_d->cost() << endl;
    my_coffee_d = new MilkDecorator(my_coffee);
    cout << "Description: " << my_coffee_d->description() << " - cost: " << my_coffee_d->cost() << endl;
    my_coffee_d = new WipDecorator(my_coffee_d);
    cout << "Description: " << my_coffee_d->description() << " - cost: " << my_coffee_d->cost() << endl;
    return 0;
}