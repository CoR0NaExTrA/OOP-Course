#pragma once
#include "Actor.h"
#include "Bank.h"

class Apu : public Actor {
private:
    Bank& bank;
    Money electricityBill; // Счёт за электроэнергию
    Actor& burns;          // Мистер Бернс (получатель платежей)

public:
    Apu(Bank& bank, Actor& burns, Money initialCash, Money electricityBill);

    void Act() override;
};
