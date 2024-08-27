#include <iostream>
#include <string>
using namespace std;

// https://stackoverflow.com/questions/67478355/unexpected-out-virtual-function-returning-string


struct Vehicle {
    virtual string drive() const =0;
    virtual ~Vehicle() {};
};

struct Car: public Vehicle {
    string drive() const override {return "CAR is driving";};
};

struct Bike: public Vehicle {
    string message = "CAR is driving";
    string drive() const override {return message;};
};

struct VehicleFactory {
    virtual Vehicle* CreateVehicle()=0;
    Vehicle* deliver_vehicle() {
        Vehicle* vehicle = CreateVehicle();
        return vehicle;
    };
};




int main() {

}