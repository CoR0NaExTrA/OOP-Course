#include "Actor.h"

// Конструктор с инициализацией имени и наличных денег
Actor::Actor(std::string name, Money initialCash, Bank& bank)
    : name(std::move(name)), wallet(initialCash), bankAccount(bank) {}

// Метод для получения наличных денег
void Actor::ReceiveCash(Money amount) {
    wallet.AddCash(amount); // Добавляем деньги в кошелёк
}

// Метод для перевода наличных денег другому персонажу
bool Actor::PayWithCash(Actor& recipient, Money amount) {
    if (wallet.SpendCash(amount)) {
        recipient.ReceiveCash(amount); // Передаем деньги
        return true;
    }
    return false; // Если не хватает наличных
}
