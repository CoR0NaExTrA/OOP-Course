#pragma once
#include "Actor.h"
#include "Bank.h"
#include "Wallet.h"

class BartLisa : public Actor {
private:
    Actor& apu;  // Апу, у которого они покупают товары

public:
    BartLisa(std::string name, Money initialCash, Bank& bank, Actor& apu);

    void Act() override;
};
