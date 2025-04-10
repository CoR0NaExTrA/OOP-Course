#include "../Economy/CBank.h"
#include <iostream>

ÑBank::ÑBank(Money initialCash) 
{
    if (initialCash < 0) 
    {
        throw BankOperationError("Initial cash cannot be negative");
    }
    cash = initialCash;
}

void ÑBank::ValidateAccount(AccountId accountId) const 
{
    if (accounts.find(accountId) == accounts.end()) 
    {
        throw BankOperationError("Account does not exist");
    }
}

void ÑBank::ValidateAmount(Money amount) const 
{
    if (amount < 0) 
    {
        throw std::out_of_range("Amount cannot be negative");
    }
}

AccountId ÑBank::OpenAccount() 
{
    AccountId accountId = nextAccountId++;
    accounts[accountId] = 0;
    return accountId;
}

Money ÑBank::CloseAccount(AccountId accountId) 
{
    ValidateAccount(accountId);
    Money balance = accounts[accountId];
    cash += balance;
    accounts.erase(accountId);
    return balance;
}

Money ÑBank::GetCash() const 
{
    return cash;
}

Money ÑBank::GetAccountBalance(AccountId accountId) const 
{
    ValidateAccount(accountId);
    return accounts.at(accountId);
}

void ÑBank::DepositMoney(AccountId accountId, Money amount) 
{
    ValidateAmount(amount);
    ValidateAccount(accountId);
    if (cash < amount) 
    {
        throw BankOperationError("Not enough cash available");
    }
    cash -= amount;
    accounts[accountId] += amount;
}

void ÑBank::WithdrawMoney(AccountId accountId, Money amount) 
{
    ValidateAmount(amount);
    ValidateAccount(accountId);
    if (accounts[accountId] < amount) 
    {
        throw BankOperationError("Insufficient funds");
    }
    accounts[accountId] -= amount;
    cash += amount;
}

bool ÑBank::TryWithdrawMoney(AccountId accountId, Money amount) 
{
    try
    {
        WithdrawMoney(accountId, amount);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
        return false;
    }

    return true;
}

void ÑBank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount) 
{
    ValidateAmount(amount);
    ValidateAccount(srcAccountId);
    ValidateAccount(dstAccountId);
    if (accounts[srcAccountId] < amount) {
        throw BankOperationError("Insufficient funds");
    }
    accounts[srcAccountId] -= amount;
    accounts[dstAccountId] += amount;
}

bool ÑBank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
    try
    {
        SendMoney(srcAccountId, dstAccountId, amount);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
        return false;
    }

    return true;
}
