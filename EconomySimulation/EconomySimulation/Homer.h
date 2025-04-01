#pragma once
#include "Actor.h"

// Класс Гомера
class Homer : public Actor {
public:
    Homer();
    void Act(Bank& bank) override;
    std::string GetName() const override;
private:
    long long salary;  // Зарплата Гомера
};