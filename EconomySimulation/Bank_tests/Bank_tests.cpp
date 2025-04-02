#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../EconomySimulation/Bank.h"

TEST_CASE("Bank initialization", "[Bank]") {
    REQUIRE_THROWS_AS(Bank(-100), BankOperationError);
    REQUIRE_NOTHROW(Bank(1000));
}

TEST_CASE("Account operations", "[Bank]") {
    Bank bank(1000);
    AccountId acc1 = bank.OpenAccount();
    AccountId acc2 = bank.OpenAccount();

    REQUIRE(bank.GetAccountBalance(acc1) == 0);
    REQUIRE(bank.GetAccountBalance(acc2) == 0);

    bank.DepositMoney(acc1, 500);
    REQUIRE(bank.GetAccountBalance(acc1) == 500);
    REQUIRE(bank.GetCash() == 500);

    REQUIRE_THROWS_AS(bank.DepositMoney(acc1, 600), BankOperationError);
    REQUIRE_THROWS_AS(bank.DepositMoney(999, 100), BankOperationError);
}

TEST_CASE("Withdraw operations", "[Bank]") {
    Bank bank(1000);
    AccountId acc1 = bank.OpenAccount();
    bank.DepositMoney(acc1, 500);

    REQUIRE_NOTHROW(bank.WithdrawMoney(acc1, 200));
    REQUIRE(bank.GetAccountBalance(acc1) == 300);
    REQUIRE(bank.GetCash() == 700);

    REQUIRE_THROWS_AS(bank.WithdrawMoney(acc1, 400), BankOperationError);
    REQUIRE_THROWS_AS(bank.WithdrawMoney(999, 100), BankOperationError);
}

TEST_CASE("Money transfers", "[Bank]") {
    Bank bank(1000);
    AccountId acc1 = bank.OpenAccount();
    AccountId acc2 = bank.OpenAccount();
    bank.DepositMoney(acc1, 500);

    REQUIRE_NOTHROW(bank.SendMoney(acc1, acc2, 200));
    REQUIRE(bank.GetAccountBalance(acc1) == 300);
    REQUIRE(bank.GetAccountBalance(acc2) == 200);

    REQUIRE_THROWS_AS(bank.SendMoney(acc1, acc2, 400), BankOperationError);
    REQUIRE_THROWS_AS(bank.SendMoney(999, acc2, 100), BankOperationError);
    REQUIRE_THROWS_AS(bank.SendMoney(acc1, 999, 100), BankOperationError);
    REQUIRE_THROWS_AS(bank.SendMoney(acc1, acc2, -100), std::out_of_range);
}
