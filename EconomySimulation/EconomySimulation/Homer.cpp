#include "Bank.h"
#include "Actor.h"

class Homer : public Actor {
public:
    // Конструктор для Гомера
    Homer(Bank& bank)
        : Actor("Homer", 1000, bank) {}

    // Специфическое поведение Гомера (например, он покупает пиво)
    void Act() override {
        std::cout << name << " is going to buy beer." << std::endl;

        // Гомер тратит деньги на пиво (например, 150)
        if (PayWithCash(*this, 150)) {
            std::cout << name << " bought beer for 150." << std::endl;
        }
        else {
            std::cout << name << " doesn't have enough cash to buy beer!" << std::endl;
        }

        // Гомер кладёт деньги на банковский счёт
        DepositToBank(200);
        std::cout << name << " deposited 200 into the bank." << std::endl;
    }
};
