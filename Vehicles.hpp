#ifndef VEHICLES
#define VEHICLES

#include <variant>
#include <iostream>
#include <fstream>

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

    virtual void serialize(std::ofstream &out) const
    {
        size_t length = brand.size();
        out.write(reinterpret_cast<const char *>(&length), sizeof(length));
        out.write(brand.c_str(), length);
        length = model.size();
        out.write(reinterpret_cast<const char *>(&length), sizeof(length));
        out.write(model.c_str(), length);
    }

    virtual void deserialize(std::ifstream &in)
    {
        size_t length;
        in.read(reinterpret_cast<char *>(&length), sizeof(length));
        brand.resize(length);
        in.read(&brand[0], length);
        in.read(reinterpret_cast<char *>(&length), sizeof(length));
        model.resize(length);
        in.read(&model[0], length);
    }

    virtual std::string getType() const = 0;
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

    void serialize(std::ofstream &out) const override
    {
        Vehicle::serialize(out);
    }

    void deserialize(std::ifstream &in) override
    {
        Vehicle::deserialize(in);
    }

    std::string getType() const override
    {
        return "Car";
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

    void serialize(std::ofstream &out) const override
    {
        Vehicle::serialize(out);
    }

    void deserialize(std::ifstream &in) override
    {
        Vehicle::deserialize(in);
    }

    std::string getType() const override
    {
        return "Motorcycle";
    }
};
#endif // VEHICLES
