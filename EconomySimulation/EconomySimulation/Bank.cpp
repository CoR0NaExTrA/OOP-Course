#include "Bank.h"

Bank::Bank(Money initialCash) {
    if (initialCash < 0) {
        throw BankOperationError("Initial cash cannot be negative");
    }
    cash = initialCash;
}

void Bank::ValidateAccount(AccountId accountId) const {
    if (accounts.find(accountId) == accounts.end()) {
        throw BankOperationError("Account does not exist");
    }
}

void Bank::ValidateAmount(Money amount) const {
    if (amount < 0) {
        throw std::out_of_range("Amount cannot be negative");
    }
}

AccountId Bank::OpenAccount() {
    AccountId accountId = nextAccountId++;
    accounts[accountId] = 0;
    return accountId;
}

Money Bank::CloseAccount(AccountId accountId) {
    ValidateAccount(accountId);
    Money balance = accounts[accountId];
    cash += balance;
    accounts.erase(accountId);
    return balance;
}

Money Bank::GetCash() const {
    return cash;
}

Money Bank::GetAccountBalance(AccountId accountId) const {
    ValidateAccount(accountId);
    return accounts.at(accountId);
}

void Bank::DepositMoney(AccountId accountId, Money amount) {
    ValidateAmount(amount);
    ValidateAccount(accountId);
    if (cash < amount) {
        throw BankOperationError("Not enough cash available");
    }
    cash -= amount;
    accounts[accountId] += amount;
}

void Bank::WithdrawMoney(AccountId accountId, Money amount) {
    ValidateAmount(amount);
    ValidateAccount(accountId);
    if (accounts[accountId] < amount) {
        throw BankOperationError("Insufficient funds");
    }
    accounts[accountId] -= amount;
    cash += amount;
}

bool Bank::TryWithdrawMoney(AccountId accountId, Money amount) {
    ValidateAmount(amount);
    ValidateAccount(accountId);
    if (accounts[accountId] < amount) {
        return false;
    }
    accounts[accountId] -= amount;
    cash += amount;
    return true;
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount) {
    ValidateAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);
    if (accounts[srcAccountId] < amount) {
        throw BankOperationError("Insufficient funds");
    }
    accounts[srcAccountId] -= amount;
    accounts[dstAccountId] += amount;
}

bool Bank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount) {
    ValidateAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);
    if (accounts[srcAccountId] < amount) {
        return false;
    }
    accounts[srcAccountId] -= amount;
    accounts[dstAccountId] += amount;
    return true;
}
