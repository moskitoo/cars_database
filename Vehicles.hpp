#ifndef VEHICLES
#define VEHICLES

#include <variant>
#include <iostream>

class Vehicle
{
private:
    std::string brand;
    std::string model;

public:
    Vehicle(const std::string &b, const std::string &mdl) : brand(b), model(mdl) {}

    virtual void display() const
    {
        std::cout << "Brand: " << brand << ", Model: " << model << std::endl;
    }

    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
    // private:
    //     int numberOfDoors;

public:
    Car(const std::string &b, const std::string &mdl)
        : Vehicle(b, mdl) {}

    // void display() const override
    // {
    //     Vehicle::display();
    //     std::cout << "Number of doors: " << numberOfDoors << std::endl;
    // }
};

class Motorcycle : public Vehicle
{
    // private:
    //     int engineCapacity;

public:
    Motorcycle(const std::string &b, const std::string &mdl)
        : Vehicle(b, mdl) {}

    // void display() const override
    // {
    //     Vehicle::display();
    //     std::cout << "Engine capacity: " << engineCapacity << "ccm" << std::endl;
    // }
};
#endif // VEHICLES
