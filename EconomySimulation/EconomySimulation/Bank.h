#pragma once
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class Bank {
private:
    Money cash;
    AccountId nextAccountId = 1;
    std::unordered_map<AccountId, Money> accounts;
public:
    explicit Bank(Money initialCash);
    AccountId OpenAccount();
    Money CloseAccount(AccountId accountId);
    void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
    bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
    Money GetCash() const;
    Money GetAccountBalance(AccountId accountId) const;
    void WithdrawMoney(AccountId accountId, Money amount);
    bool TryWithdrawMoney(AccountId accountId, Money amount);
    void DepositMoney(AccountId accountId, Money amount);
};
