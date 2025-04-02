#include "BartLisa.h"
#include <iostream>

BartLisa::BartLisa(std::string name, Money initialCash, Bank& bank, Actor& apu)
    : Actor(std::move(name), initialCash, bank), apu(apu) {
}

void BartLisa::Act() {
    Money purchaseAmount = 5; // Фиксированная сумма покупки

    if (PayWithCash(apu, purchaseAmount)) {
        std::cout << name << " купил товар у Апу за " << purchaseAmount << " наличными.\n";
    }
    else {
        std::cout << name << " не хватает наличных для покупки.\n";
    }
}

