#include "Homer.h"
#include <iostream>

Homer::Homer(Bank& bank, Actor& marge, Actor& burns, std::vector<Actor*> children,
    Money initialCash, Money allowance, Money bill, Money kidsCash)
    : Actor("Homer", initialCash, bank), bank(bank), marge(marge), burns(burns),
    allowanceForMarge(allowance), electricityBill(bill), cashForKids(kidsCash), children(std::move(children)) {
    bankAccount.OpenAccount(); // Открываем счёт
}

void Homer::Act() {
    // Перевод денег Мардж
    if (GetBankBalance() >= allowanceForMarge) {
        bank.SendMoney(bankAccount.GetAccountId().value(), marge.GetBankAccount().GetAccountId().value(), allowanceForMarge);
        std::cout << name << " перевёл " << allowanceForMarge << " на счёт Мардж.\n";
    }
    else {
        std::cout << name << " не хватает денег для перевода Мардж.\n";
    }

    // Оплата счета за электричество мистеру Бернсу
    if (GetBankBalance() >= electricityBill) {
        bank.SendMoney(bankAccount.GetAccountId().value(), burns.GetBankAccount().GetAccountId().value(), electricityBill);
        std::cout << name << " оплатил " << electricityBill << " за электричество мистеру Бернсу.\n";
    }
    else {
        std::cout << name << " не хватает денег на оплату электричества.\n";
    }

    // Раздача наличных детям
    for (Actor* child : children) {
        if (GetBankBalance() >= cashForKids) {
            WithdrawFromBank(cashForKids);
            child->ReceiveCash(cashForKids);
            std::cout << name << " дал " << cashForKids << " наличными " << child->GetName() << ".\n";
        }
    }
}
