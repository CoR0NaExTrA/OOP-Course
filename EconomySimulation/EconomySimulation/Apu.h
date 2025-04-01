#pragma once
#include "Actor.h"

// Класс Апу
class Apu : public Actor {
public:
    Apu();
    void Act(Bank& bank) override;
    std::string GetName() const override;
private:
    long long electricityPayment;  // Платежи за электричество
};