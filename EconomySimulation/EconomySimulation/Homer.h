#pragma once
#include "Actor.h"
#include "Bank.h"

class Homer : public Actor {
private:
    Bank& bank;
    Money allowanceForMarge;  // Денежное пособие для Мардж
    Money electricityBill;    // Оплата электричества
    Money cashForKids;        // Карманные деньги детям
    Actor& marge;
    Actor& burns;
    std::vector<Actor*> children; // Дети (Барт и Лиза)

public:
    Homer(Bank& bank, Actor& marge, Actor& burns, std::vector<Actor*> children,
        Money initialCash, Money allowance, Money bill, Money kidsCash);

    void Act() override;
};
