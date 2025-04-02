#include "Marge.h"
#include <iostream>

Marge::Marge(Bank& bank) : Actor("Marge", 500, bank) {}

void Marge::Act() {
    std::cout << name << " is saving money." << std::endl;

    DepositToBank(100);
    std::cout << name << " deposited 100 into the bank." << std::endl;

    if (WithdrawFromBank(50)) {
        std::cout << name << " withdrew 50 from the bank." << std::endl;
    }
    else {
        std::cout << name << " couldn't withdraw money from the bank!" << std::endl;
    }
}
