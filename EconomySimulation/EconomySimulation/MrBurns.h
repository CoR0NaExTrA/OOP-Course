#pragma once
#include "Actor.h"
#include "Bank.h"

class MrBurns : public Actor {
private:
    Bank& bank;
    Money salaryForHomer;  // Зарплата для Гомера
    Actor& homer;

public:
    MrBurns(Bank& bank, Money initialCash, Money salary, Actor& homer);

    void Act() override;
};
