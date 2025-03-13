#include "Car.h"

Car::Car() : engineOn(false), speed(0), gear(0) 
{
    gearSpeeds = 
    {
        {-1, {0, 20}}, {1, {0, 30}}, {2, {20, 50}}, {3, {30, 60}},
        {4, {40, 90}}, {5, {50, 150}}
    };
}

bool Car::TurnOnEngine() 
{
    engineOn = true;
    return true;
}

bool Car::TurnOffEngine() 
{
    if (!engineOn)
    {
        return false;
    }
    if (speed == 0 && gear == 0) 
    {
        engineOn = false;
        return true;
    }
    std::cout << "Car must be stopped and in neutral gear" << std::endl;
    return false;
}

bool Car::SetGear(int newGear) 
{
    if (!engineOn) 
    {
        std::cout << "Ñannot set gear while engine is off" << std::endl;
        return false;
    }
    if (newGear < -1 || newGear > 5) 
    {
        std::cout << "Invalid gear" << std::endl;
        return false;
    }
    if (newGear == -1 && speed != 0) 
    {
        std::cout << "Cannot reverse while moving" << std::endl;
        return false;
    }
    if (gear == -1 && newGear > 0 && speed != 0) 
    {
        std::cout << "Cannot switch from reverse to forward while moving" << std::endl;
        return false;
    }
    if (gearSpeeds.find(newGear) != gearSpeeds.end()) 
    {
        auto range = gearSpeeds[newGear];
        if (speed < range.first || speed > range.second) 
        {
            std::cout << "Unsuitable current speed" << std::endl;
            return false;
        }
    }
    gear = newGear;
    return true;
}

bool Car::SetSpeed(int newSpeed)
{
    if (newSpeed < 0)
    {
        std::cout << "Speed cannot be negative" << std::endl;
        return false;
    }
    if (!engineOn)
    {
        std::cout << "Cannot set speed while engine is off" << std::endl;
        return false;
    }
    if (gear == 0 && newSpeed > speed)
    {
        std::cout << "Cannot accelerate on neutral" << std::endl;
        return false;
    }
    if (gearSpeeds.find(gear) != gearSpeeds.end())
    {
        auto range = gearSpeeds[gear];
        if (newSpeed < range.first || newSpeed > range.second)
        {
            std::cout << "Speed is out of gear range" << std::endl;
            return false;
        }
    }
    speed = newSpeed;
    return true;
}

void Car::Info() const 
{
    std::cout << "Engine: " << (engineOn ? "on" : "off") << "\n";
    std::cout << "Direction: " << GetDirection() << "\n";
    std::cout << "Speed: " << speed << "\n";
    std::cout << "Gear: " << gear << "\n";
}

std::string Car::GetDirection() const {
    if (speed == 0) return "standing still";
    return (gear == -1) ? "backward" : "forward";
}
