#pragma once
#include "Actor.h"
#include "Bank.h"

class Homer : public Actor {
private:
    Bank& bank;  // Ссылка на банк
    Actor& marge;  // Ссылка на Мардж
    std::vector<Actor*> children;  // Список детей

    const Money ALLOWANCE_FOR_MARGE;
    const Money ELECTRICITY_BILL;
    const Money CASH_FOR_KIDS;

public:
    Homer(Bank& bank, Actor& marge, std::vector<Actor*> kids, Money initialCash, Money allowance, Money bill, Money kidsCash);

    void Act() override;
};
