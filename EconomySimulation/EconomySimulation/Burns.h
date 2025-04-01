#pragma once
#include "Actor.h"

// Класс Мистер Бернс
class Burns : public Actor {
public:
    Burns();
    void Act(Bank& bank) override;
    std::string GetName() const override;
private:
    long long salaryPayment;  // Зарплата Гомеру
};