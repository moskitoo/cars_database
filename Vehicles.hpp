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
    virtual ~Vehicle() {}

    virtual void display() const
    {
        std::cout << "Brand: " << brand << ", Model: " << model << ", ";
    }

};

class Car : public Vehicle
{

public:
    Car(const std::string &b, const std::string &mdl)
        : Vehicle(b, mdl) {}

    void display() const
    {
        Vehicle::display();
        std::cout << "Recquired age: 18" << std::endl;
    }
};

class Motorcycle : public Vehicle
{

public:
    Motorcycle(const std::string &b, const std::string &mdl)
        : Vehicle(b, mdl) {}

    void display() const // override
    {
        Vehicle::display();
        std::cout << "Recquired age: 24" << std::endl;
    }
};
#endif // VEHICLES
