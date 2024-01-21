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

        if (file.is_open())
        {
            for (const auto &type : vehicles)
            {
                for (const auto &vehicle : type.second)
                {
                    file.write(reinterpret_cast<const char *>(vehicle.get()), sizeof(Vehicle));
                }
            }

            file.close();
            std::cout << "Database saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
        }
    }

    void readFromFile(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);

        vehicles.clear();

        if (file.is_open())
        {
            while (!file.eof())
            {
                std::unique_ptr<Vehicle> vehicle = std::make_unique<Vehicle>("", "");

                file.read(reinterpret_cast<char *>(vehicle.get()), sizeof(Vehicle));

                if (dynamic_cast<Car *>(vehicle.get()))
                {
                    addVehicle(std::move(vehicle));
                }
                else if (dynamic_cast<Motorcycle *>(vehicle.get()))
                {
                    addVehicle(std::move(vehicle));
                }
            }

            file.close();
            std::cout << "Database loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
        }
    }
};

#endif // DATABASE