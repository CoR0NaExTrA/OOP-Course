#include "Marge.h"
#include <iostream>

Marge::Marge(Bank& bank, Actor& apu, Money initialCash, Money groceryBudget)
    : Actor("Marge", initialCash, bank), bank(bank), apu(apu), groceryBudget(groceryBudget) {
    bankAccount.OpenAccount(); // Открываем счёт
}

void Marge::Act() {
    // Покупка продуктов у Апу
    if (GetBankBalance() >= groceryBudget) {
        bank.SendMoney(bankAccount.GetAccountId().value(), apu.GetBankAccount().GetAccountId().value(), groceryBudget);
        std::cout << name << " купила продукты у Апу за " << groceryBudget << ".\n";
    }
    else {
        std::cout << name << " не хватает денег на продукты.\n";
    }
}
