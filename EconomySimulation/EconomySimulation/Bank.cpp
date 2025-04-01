#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include "Bank.h"

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class Bank {
public:
    explicit Bank(Money cash) {
        if (cash < 0) {
            throw BankOperationError("Initial cash cannot be negative");
        }
        cash_in_circulation = cash;
    }

    AccountId OpenAccount() {
        AccountId newId = nextAccountId++;
        accounts[newId] = 0;
        return newId;
    }

    Money CloseAccount(AccountId accountId) {
        auto it = accounts.find(accountId);
        if (it == accounts.end()) {
            throw BankOperationError("Account not found");
        }
        Money balance = it->second;
        cash_in_circulation += balance;
        accounts.erase(it);
        return balance;
    }

    void DepositMoney(AccountId account, Money amount) {
        if (amount < 0) {
            throw std::out_of_range("Cannot deposit negative amount");
        }
        if (cash_in_circulation < amount) {
            throw BankOperationError("Not enough cash in circulation");
        }
        auto it = accounts.find(account);
        if (it == accounts.end()) {
            throw BankOperationError("Account not found");
        }
        it->second += amount;
        cash_in_circulation -= amount;
    }

    void WithdrawMoney(AccountId account, Money amount) {
        if (amount < 0) {
            throw std::out_of_range("Cannot withdraw negative amount");
        }
        auto it = accounts.find(account);
        if (it == accounts.end()) {
            throw BankOperationError("Account not found");
        }
        if (it->second < amount) {
            throw BankOperationError("Insufficient funds");
        }
        it->second -= amount;
        cash_in_circulation += amount;
    }

    bool TryWithdrawMoney(AccountId account, Money amount) {
        try {
            WithdrawMoney(account, amount);
            return true;
        }
        catch (const BankOperationError&) {
            return false;
        }
    }

    void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount) {
        if (amount < 0) {
            throw std::out_of_range("Cannot send negative amount");
        }
        auto srcIt = accounts.find(srcAccountId);
        auto dstIt = accounts.find(dstAccountId);
        if (srcIt == accounts.end() || dstIt == accounts.end()) {
            throw BankOperationError("Invalid account");
        }
        if (srcIt->second < amount) {
            throw BankOperationError("Insufficient funds");
        }
        srcIt->second -= amount;
        dstIt->second += amount;
    }

    bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount) {
        try {
            SendMoney(srcAccountId, dstAccountId, amount);
            return true;
        }
        catch (const BankOperationError&) {
            return false;
        }
    }

    Money GetCash() const {
        return cash_in_circulation;
    }

    Money GetAccountBalance(AccountId accountId) const {
        auto it = accounts.find(accountId);
        if (it == accounts.end()) {
            throw BankOperationError("Account not found");
        }
        return it->second;
    }

private:
    Money cash_in_circulation;
    AccountId nextAccountId = 1;
    std::unordered_map<AccountId, Money> accounts;
};
