#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Bank.h"
#include "Wallet.h"
#include "BankAccount.h"

class Actor {
protected:
    std::string name;
    Wallet wallet;
    BankAccount bankAccount;

public:
    Actor(std::string name, Money initialCash, Bank& bank);
    virtual ~Actor() = default;

    virtual void Act() = 0;

    void ReceiveCash(Money amount);
    bool PayWithCash(Actor& recipient, Money amount);
    // Метод для пополнения банковского счёта
    void DepositToBank(Money amount) {
        bankAccount.Deposit(amount); // Пополняем счёт
    }

    // Метод для снятия денег с банковского счёта
    bool WithdrawFromBank(Money amount) {
        return bankAccount.Withdraw(amount); // Снимаем деньги
    }

    // Метод для получения баланса банковского счёта
    [[nodiscard]] Money GetBankBalance() const {
        return bankAccount.GetBalance(); // Получаем баланс счёта
    }

    // Метод для получения количества наличных
    [[nodiscard]] Money GetCash() const {
        return wallet.GetCash(); // Получаем сумму наличных
    }

    [[nodiscard]] BankAccount& GetBankAccount() {
        return bankAccount;
    }

    [[nodiscard]] const std::string& GetName() const {
        return name;
    }
};
