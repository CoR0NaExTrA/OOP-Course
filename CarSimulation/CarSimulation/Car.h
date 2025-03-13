#pragma once
#include <iostream>
#include <map>
#include <string>

class Car 
{
public:
    Car();
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int newGear);
    bool SetSpeed(int newSpeed);
    void Info() const;

private:
    bool engineOn;
    int speed;
    int gear;
    std::map<int, std::pair<int, int>> gearSpeeds;
    std::string GetDirection() const;
};