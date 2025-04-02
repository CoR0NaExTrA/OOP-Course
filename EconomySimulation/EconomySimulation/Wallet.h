#pragma once
#include "Bank.h"

class Wallet {
private:
    Money cash;

public:
    explicit Wallet(Money initialCash) : cash(initialCash) {}

    void AddCash(Money amount);
    bool SpendCash(Money amount);
    [[nodiscard]] Money GetCash() const;
};