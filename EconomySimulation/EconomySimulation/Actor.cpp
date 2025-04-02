#include "Bank.h"
#include "Wallet.h"
#include "BankAccount.h"
#include "Actor.h"

class Actor {
protected:
    std::string name;           // Имя персонажа
    Wallet wallet;              // Объект кошелька для наличных денег
    BankAccount bankAccount;    // Объект банковского счёта

public:
    // Конструктор с инициализацией имени и наличных денег
    Actor(std::string name, Money initialCash, Bank& bank)
        : name(std::move(name)), wallet(initialCash), bankAccount(bank) {}

    virtual ~Actor() = default; // Виртуальный деструктор для наследников

    // Чисто виртуальный метод для действия персонажа
    virtual void Act() = 0;

    // Метод для получения наличных денег
    void ReceiveCash(Money amount) {
        wallet.AddCash(amount); // Добавляем деньги в кошелёк
    }

    // Метод для перевода наличных денег другому персонажу
    bool PayWithCash(Actor& recipient, Money amount) {
        if (wallet.SpendCash(amount)) {
            recipient.ReceiveCash(amount); // Передаем деньги
            return true;
        }
        return false; // Если не хватает наличных
    }
};
