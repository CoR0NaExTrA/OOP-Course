#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include <iostream>

int main() {
    Bank bank(10000);  // Создаём банк с 10,000 наличных

    Homer homer(bank); // Гомер с 1000 наличными
    Marge marge(bank); // Мардж с 500 наличными

    homer.Act();  // Гомер совершает действия
    marge.Act();  // Мардж совершает действия

    std::cout << "Homer cash: " << homer.GetCash() << ", Bank balance: " << homer.GetBankBalance() << std::endl;
    std::cout << "Marge cash: " << marge.GetCash() << ", Bank balance: " << marge.GetBankBalance() << std::endl;

    return 0;
}
