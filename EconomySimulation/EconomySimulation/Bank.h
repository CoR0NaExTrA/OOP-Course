#pragma once
#include <stdexcept>
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class Bank {
public:
    explicit Bank(Money cash);
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;

    void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
    [[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

    [[nodiscard]] Money GetCash() const;
    Money GetAccountBalance(AccountId accountId) const;

    void WithdrawMoney(AccountId account, Money amount);
    [[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);

    void DepositMoney(AccountId account, Money amount);
    [[nodiscard]] AccountId OpenAccount();
    [[nodiscard]] Money CloseAccount(AccountId accountId);

private:
    Money cash;
    std::unordered_map<AccountId, Money> accounts;
    AccountId nextAccountId = 1;

    void ValidateAccount(AccountId accountId) const;
    void ValidateAmount(Money amount) const;
};
