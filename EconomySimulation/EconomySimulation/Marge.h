#pragma once
#include "Actor.h"

// Класс Мардж
class Marge : public Actor {
public:
    Marge();
    void Act(Bank& bank) override;
    std::string GetName() const override;
private:
    long long grocerySpending;  // Расходы на продукты
};