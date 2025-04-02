#pragma once
#include "Bank.h"
#include <optional>

class BankAccount {
private:
    Bank& bank;
    std::optional<AccountId> accountId;

public:
    explicit BankAccount(Bank& bank);

    void OpenAccount();
    void CloseAccount();
    void Deposit(Money amount);
    bool Withdraw(Money amount);
    [[nodiscard]] Money GetBalance() const;
    [[nodiscard]] bool HasAccount() const;
};
