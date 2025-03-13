#include "Car.h"

int main() 
{
    Car car;
    std::string command;
    while (std::cin >> command) 
    {
        if (command == "EngineOn") 
        {
            car.TurnOnEngine();
        }
        else if (command == "EngineOff") 
        {
            car.TurnOffEngine();
        }
        else if (command == "SetGear") 
        {
            int gear;
            if (std::cin >> gear) 
            {
                car.SetGear(gear);
            }
            else {
                std::cout << "Invalid command argument" << std::endl;
            }
        }
        else if (command == "SetSpeed") 
        {
            int speed;
            if (std::cin >> speed) 
            {
                car.SetSpeed(speed);
            }
            else 
            {
                std::cout << "Invalid command argument" << std::endl;
            }
        }
        else if (command == "Info") 
        {
            car.Info();
        }
        else if (command == "...") 
        {
            return 0;
        }
        else 
        {
            std::cout << "Unknown command" << std::endl;
        }
    }
    return 0;
}
