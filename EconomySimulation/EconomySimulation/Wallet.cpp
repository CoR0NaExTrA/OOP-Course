#include "Wallet.h"

// Метод для добавления наличных денег
void Wallet::AddCash(Money amount) {
    if (amount < 0) {
        throw std::out_of_range("Cannot add negative amount of cash");
    }
    cash += amount;
}

// Метод для траты наличных
bool Wallet::SpendCash(Money amount) {
    if (amount < 0) {
        throw std::out_of_range("Cannot spend negative amount of cash");
    }
    if (cash < amount) {
        return false;  // Недостаточно наличных
    }
    cash -= amount;
    return true;
}

// Метод для получения текущего количества наличных
Money Wallet::GetCash() const {
    return cash;
}
