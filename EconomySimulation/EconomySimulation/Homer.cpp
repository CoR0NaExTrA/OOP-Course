#include "Homer.h"
#include <iostream>

// Конструктор
Homer::Homer(Bank& bank, Actor& marge, std::vector<Actor*> kids, Money initialCash, Money allowance, Money bill, Money kidsCash)
    : Actor("Homer", initialCash, bank), bank(bank), marge(marge), children(std::move(kids)),
    ALLOWANCE_FOR_MARGE(allowance), ELECTRICITY_BILL(bill), CASH_FOR_KIDS(kidsCash) {
    bankAccount.OpenAccount(); // Открываем банковский счёт Гомера
}

// Реализация действий Гомера
void Homer::Act() {
    // Проверяем, есть ли у Гомера банковский счёт
    if (!bankAccount.HasAccount()) {
        std::cerr << name << " не имеет банковского счёта!\n";
        return;
    }

    // Перевод денег Мардж
    if (GetBankBalance() >= ALLOWANCE_FOR_MARGE) {
        if (marge.GetBankAccount().HasAccount()) {
            bank.SendMoney(bankAccount.GetAccountId().value(), marge.GetBankAccount().GetAccountId().value(), ALLOWANCE_FOR_MARGE);
            std::cout << name << " перевёл " << ALLOWANCE_FOR_MARGE << " на счёт Мардж.\n";
        }
        else {
            std::cerr << "Ошибка: Мардж не имеет банковского счёта!\n";
        }
    }

    // Оплата счёта за электричество
    if (GetBankBalance() >= ELECTRICITY_BILL) {
        bank.Withdraw(bankAccount.GetAccountId().value(), ELECTRICITY_BILL);
        std::cout << name << " оплатил " << ELECTRICITY_BILL << " за электричество.\n";
    }

    // Раздача наличных детям
    for (Actor* child : children) {
        if (GetBankBalance() >= CASH_FOR_KIDS) {
            WithdrawFromBank(CASH_FOR_KIDS);
            child->ReceiveCash(CASH_FOR_KIDS);
            std::cout << name << " дал " << CASH_FOR_KIDS << " наличными " << child->GetName() << ".\n";
        }
    }
}
