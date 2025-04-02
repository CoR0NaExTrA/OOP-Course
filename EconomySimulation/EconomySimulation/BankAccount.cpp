#include "BankAccount.h"

// Конструктор, принимающий ссылку на банк
BankAccount::BankAccount(Bank& bank) : bank(bank), accountId(std::nullopt) {}

// Открытие счёта
void BankAccount::OpenAccount() {
    if (accountId.has_value()) {
        throw BankOperationError("Account is already opened");
    }
    accountId = bank.OpenAccount(); // Открываем счёт в банке
}

// Закрытие счёта и возврат денег
void BankAccount::CloseAccount() {
    if (!accountId.has_value()) {
        throw BankOperationError("Account is not opened");
    }
    bank.CloseAccount(accountId.value()); // Закрываем счёт и забираем деньги
    accountId.reset(); // Обнуляем ID счёта
}

// Пополнение счёта
void BankAccount::Deposit(Money amount) {
    if (!accountId.has_value()) {
        throw BankOperationError("Account is not opened");
    }
    bank.DepositMoney(accountId.value(), amount); // Переводим деньги на счёт
}

// Снятие денег со счёта
bool BankAccount::Withdraw(Money amount) {
    if (!accountId.has_value()) {
        throw BankOperationError("Account is not opened");
    }
    return bank.TryWithdrawMoney(accountId.value(), amount); // Пытаемся снять деньги
}

// Получение баланса счёта
Money BankAccount::GetBalance() const {
    if (!accountId.has_value()) {
        throw BankOperationError("Account is not opened");
    }
    return bank.GetAccountBalance(accountId.value()); // Получаем баланс счёта
}

// Проверка, открыт ли счёт
bool BankAccount::HasAccount() const {
    return accountId.has_value();
}
