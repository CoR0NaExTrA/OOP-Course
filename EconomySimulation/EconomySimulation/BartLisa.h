#pragma once
#include "Actor.h"

// Класс Барт и Лиза
class BartLisa : public Actor {
public:
    BartLisa();
    void Act(Bank& bank) override;
    std::string GetName() const override;
private:
    long long spendingLimit;  // Лимит для покупок
};