#include <iostream>
#include <string>
using namespace std;

// https://stackoverflow.com/questions/67478355/unexpected-out-virtual-function-returning-string


struct Vehicle {
    virtual string drive()=0;
};

struct Car: public Vehicle {
    string drive() override {return "CAR is driving";};
};

struct Bike: public Vehicle {
    string drive() override {return "BIKE is driving";};
};

struct VehicleFactory {
    virtual Vehicle* CreateVehicle()=0;
    string deliver_vehicle() {
        Vehicle* vehicle = CreateVehicle();
        return vehicle->drive();
    };
};

struct CarFactory: VehicleFactory {
    virtual Car* CreateVehicle() override {
        return new Car();
    }
};

struct BikeFactory: VehicleFactory {
    virtual Bike* CreateVehicle() override {
        return new Bike();
    }
};

int main() {
    VehicleFactory* factories[2] = {new CarFactory(), new BikeFactory()};
    for(int i=0; i<2; i++) cout << factories[i]->deliver_vehicle() << endl;
    return 0;
}