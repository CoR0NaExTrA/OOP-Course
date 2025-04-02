#include "MrBurns.h"
#include <iostream>

MrBurns::MrBurns(Bank& bank, Money initialCash, Money salary, Actor& homer)
    : Actor("Mr. Burns", initialCash, bank), bank(bank), salaryForHomer(salary), homer(homer) {
    bankAccount.OpenAccount(); // Открываем счёт
}

void MrBurns::Act() {
    // Платим Гомеру зарплату
    if (GetBankBalance() >= salaryForHomer) {
        bank.SendMoney(bankAccount.GetAccountId().value(), homer->GetBankAccount().GetAccountId().value(), salaryForHomer);
        std::cout << name << " платит Гомеру " << salaryForHomer << " как зарплату.\n";
    }
    else {
        std::cout << name << " не хватает денег на выплату зарплаты.\n";
    }
}
