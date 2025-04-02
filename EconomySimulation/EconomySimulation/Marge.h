#pragma once
#include "Actor.h"
#include "Bank.h"

class Marge : public Actor {
private:
    Bank& bank;
    Actor& apu; // Апу, которому Мардж платит за продукты
    Money groceryBudget; // Бюджет на продукты

public:
    Marge(Bank& bank, Actor& apu, Money initialCash, Money groceryBudget);

    void Act() override;
};
