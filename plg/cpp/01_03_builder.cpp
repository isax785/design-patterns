#include <iostream>
#include <string>

using namespace std;

class House {
    public:
        string foundation;
        string structure;
        string roof;
        string interior;
        string description() {
            string s = "House with ";
            s += foundation;
            s += " foundation ";
            s += structure;
            s += " structure ";
            s += roof;
            s += " roof, and ";
            s += interior;
            s += " interior.";
            return s;
        }
};

class HouseBuilder {
    public:
        virtual void build_foundation()=0;
        virtual void build_structure()=0;
        virtual void build_roof()=0;
        virtual void build_interior()=0;
        virtual House* get_house()=0;
        virtual string get_name()=0;
        virtual void another_name(string)=0;
};

class ConcreteHouseBuilder : public HouseBuilder {
    private:
        string _house_name;
    public:
        House* house = new House;
        ConcreteHouseBuilder(string house_name) {_house_name = house_name;};
        void build_foundation() override {house->foundation="Concrete";}
        void build_structure() override {house->structure="Wood and Brick";}
        void build_roof() override {house->roof="Tile";}
        void build_interior() override {house->interior="Drywall and Paint";}
        House* get_house() override {return house;}
        string get_name() override {return _house_name;}
        void another_name(string name) override {
            cout << "House name changed from " << _house_name;
            _house_name = name;
            cout << " to " << _house_name << endl;
        }
        void concrete_method() {cout << _house_name << " CONCRETE METHOD!!!" << endl;} // just for adding a method
};

class HouseDirector {
    private:
        HouseBuilder* builder;
        ConcreteHouseBuilder* builder_concrete;
    public:
        HouseDirector(string house_name) {
            builder = new ConcreteHouseBuilder(house_name);
            builder_concrete = new ConcreteHouseBuilder(house_name+" Concrete");};
        void construct_house() {
            builder->build_foundation();
            builder->build_roof();
            builder->build_interior();
            builder->build_structure();
            cout << "Built house: " << builder->get_name() << endl;
        };
        void another_name(string name) {
            builder->another_name(name);
            // builder->concrete_method(); // cannot be called since not declared in HouseBuilder
            builder_concrete->concrete_method();
            }
};

int main() {
    ConcreteHouseBuilder* builder = new ConcreteHouseBuilder("casa");
    cout << builder->get_name() << endl;
    cout << builder->house->description() << endl;
    // available because builder is a ConcreteHouseBuilder instance
    builder->concrete_method();

    HouseDirector house_director = HouseDirector("First House");
    house_director.construct_house();
    house_director.another_name("The House");

    // not available since .builder is a HouseBuilder instance
    // house_director.builder->concrete_method(); 

    return 0;
}