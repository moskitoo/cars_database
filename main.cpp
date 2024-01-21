#include "DataBase.hpp"
#include <iostream>
#include <string>
#include <limits>

int main()
{
    Database db;
    std::string brand, model, typeToRemove;
    int indexToRemove;

    // db.addVehicle(std::make_unique<Car>("Fiat", "126p"));
    // db.addVehicle(std::make_unique<Motorcycle>("Honda", "CBR"));

    int choice;

    do
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Display all vehicles\n";
        std::cout << "2. Add a car\n";
        std::cout << "3. Add a motorcycle\n";
        std::cout << "4. Remove a vehicle\n";
        std::cout << "5. Save to file\n";
        std::cout << "6. Load from file\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        

        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number.\n";
            std::cout << "Enter your choice: ";
        }

        switch (choice)
        {
        case 1:
            std::cout << "\nAll Vehicles:\n";
            db.display_vehicles();
            break;
        case 2:
            std::cout << "\nEnter vehicle details:\n";
            std::cout << "Brand: ";
            std::cin >> brand;
            std::cout << "Model: ";
            std::cin >> model;
            db.addVehicle(std::make_unique<Car>(brand, model));
            break;
        case 3:
            std::cout << "\nEnter vehicle details:\n";
            std::cout << "Brand: ";
            std::cin >> brand;
            std::cout << "Model: ";
            std::cin >> model;
            db.addVehicle(std::make_unique<Motorcycle>(brand, model));
            break;
        case 4:
            std::cout << "\nEnter type to remove: ";
            std::cin >> typeToRemove;
            std::cout << "\nEnter index to remove: ";
            std::cin >> indexToRemove;
            db.removeVehicle(typeToRemove, indexToRemove);
            break;
        case 5:
            db.saveToFile("database.bin");
            break;
        case 6:
            db.readFromFile("database.bin");
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}