#include "Apu.h"
#include <iostream>

Apu::Apu(Bank& bank, Actor& burns, Money initialCash, Money electricityBill)
    : Actor("Apu", initialCash, bank), bank(bank), burns(burns), electricityBill(electricityBill) {
    bankAccount.OpenAccount(); // Открываем счёт
}

void Apu::Act() {
    // Оплата счета за электроэнергию мистеру Бернсу
    if (GetBankBalance() >= electricityBill) {
        bank.SendMoney(bankAccount.GetAccountId().value(), burns.GetBankAccount().GetAccountId().value(), electricityBill);
        std::cout << name << " оплатил " << electricityBill << " за электричество мистеру Бернсу.\n";
    }
    else {
        std::cout << name << " не хватает денег на оплату электричества.\n";
    }

    // Перемещение наличных на банковский счёт
    if (GetCash() > 0) {
        Money cash = GetCash(); // Запоминаем сумму перед пополнением
        DepositToBank(cash);
        std::cout << name << " положил " << cash << " на банковский счёт.\n";
    }
}
