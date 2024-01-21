#ifndef DATABASE
#define DATABASE

#include "Vehicles.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <memory>

class Database
{
private:
    std::map<std::string, std::vector<std::unique_ptr<Vehicle>>> vehicles;

public:
    Database() {}
    virtual ~Database() {}

    void addVehicle(std::unique_ptr<Vehicle> new_vehicle)
    {
        if (dynamic_cast<Car *>(new_vehicle.get()))
        {
            vehicles["car"].push_back(std::move(new_vehicle));
        }
        else
        {
            vehicles["motor"].push_back(std::move(new_vehicle));
        }
    }

    void removeVehicle(std::string type, int index)
    {
        auto it = vehicles.find(type);
        if (it != vehicles.end() && index < it->second.size())
        {
            it->second.erase(it->second.begin() + index);
            std::cout << "Vehicle at index " << index << " deleted from " << type << std::endl;
        }
        else
        {
            std::cout << "Invalid index or key not found." << std::endl;
        }
    }

    void display_vehicles()
    {
        for (const auto &type : vehicles)
        {
            std::cout << "\n"
                      << type.first << ":\n"
                      << std::endl;

            int iterator = 0;

            for (const auto &vehicle : type.second)
            {
                std::cout << iterator << ": ";
                vehicle->display();
                iterator++;
            }
        }
    }

    void saveToFile(const std::string &filename)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        for (const auto &type : vehicles)
        {
            for (const auto &vehicle : type.second)
            {
                std::string type = vehicle->getType();
                file.write(type.c_str(), type.size());
                vehicle->serialize(file);
            }
        }

        file.close();
        std::cout << "Database saved to file: " << filename << std::endl;
    }

    void readFromFile(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return;
        }

        vehicles.clear();

        while (!file.eof())
        {
            char type[20];
            file.read(type, sizeof(type));
            std::string vehicleType(type);

            std::unique_ptr<Vehicle> vehicle;
            if (vehicleType == "Car")
            {
                vehicle = std::make_unique<Car>("", "");
            }
            else if (vehicleType == "Motorcycle")
            {
                vehicle = std::make_unique<Motorcycle>("", "");
            }
            else
            {
                break;
            }

            vehicle->deserialize(file);
            addVehicle(std::move(vehicle));
        }

        file.close();
        std::cout << "Database loaded from file: " << filename << std::endl;
    }
};

#endif // DATABASE