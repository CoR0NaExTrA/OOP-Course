#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../Economy/CBank.h"
#include "../Economy/Actors.h"
#include "../Economy/CActor.h"

TEST_CASE("Bank initialization", "[Bank]") {
    REQUIRE_THROWS_AS(СBank(-100), BankOperationError);
    REQUIRE_NOTHROW(СBank(1000));
}

TEST_CASE("Account open and close", "[Bank]") {
    СBank bank(1000);
    AccountId acc1 = bank.OpenAccount();
    AccountId acc2 = bank.OpenAccount();

    REQUIRE(bank.GetAccountBalance(acc1) == 0);
    REQUIRE(bank.GetAccountBalance(acc2) == 0);

    REQUIRE_THROWS_AS(bank.GetAccountBalance(-1), BankOperationError);
    REQUIRE_THROWS_AS(bank.CloseAccount(-1), BankOperationError);
    Money moneyAcc2 = bank.CloseAccount(acc2);
    CHECK(moneyAcc2 == 0);
    REQUIRE_THROWS_AS(bank.GetAccountBalance(acc2), BankOperationError);
}

TEST_CASE("Transfer operations", "[Bank]") {
    СBank bank(1000);
    AccountId acc1 = bank.OpenAccount();
    AccountId acc2 = bank.OpenAccount();

    REQUIRE_THROWS_AS(bank.DepositMoney(acc1, 1001), BankOperationError);
    REQUIRE_THROWS_AS(bank.DepositMoney(acc1, -1), std::out_of_range);

    bank.DepositMoney(acc1, 500);
    CHECK(bank.GetAccountBalance(acc1) == 500);
    CHECK(bank.GetCash() == 500);

    REQUIRE_THROWS_AS(bank.SendMoney(acc1, -1, 25), BankOperationError);
    REQUIRE_THROWS_AS(bank.SendMoney(-1, acc1, 25), BankOperationError);

    REQUIRE_THROWS_AS(bank.SendMoney(acc1, acc2, 501), BankOperationError);
    REQUIRE_THROWS_AS(bank.SendMoney(acc1, acc2, -25), std::out_of_range);

    REQUIRE_NOTHROW(bank.SendMoney(acc1, acc2, 200));
    REQUIRE(bank.GetAccountBalance(acc1) == 300);
    REQUIRE(bank.GetAccountBalance(acc2) == 200);

    REQUIRE_THROWS_AS(bank.WithdrawMoney(acc2, -10), std::out_of_range);
    REQUIRE_THROWS_AS(bank.WithdrawMoney(-1, 100), BankOperationError);
    REQUIRE_THROWS_AS(bank.WithdrawMoney(acc2, 201), BankOperationError);
}

TEST_CASE("Homer test", "[Bank]") {
    СBank bank(1000);
    Springfield springfield;
    springfield.Homer = new Homer(500, bank);
    springfield.Marge = new Marge(0, bank);
    springfield.MrBurns = new MrBurns(0, bank);
    springfield.Lisa = new Lisa(0);
    springfield.Bart = new Bart(0);

    springfield.Homer->OpenAccount();
    springfield.Marge->OpenAccount();
    springfield.MrBurns->OpenAccount();

    springfield.Homer->DepositMoney(500);
    springfield.Homer->Act(springfield);

    REQUIRE(bank.GetAccountBalance(springfield.Marge->GetAccountId()) == 100);
    REQUIRE(bank.GetAccountBalance(springfield.MrBurns->GetAccountId()) == 250);
    REQUIRE(springfield.Lisa->GetCash() == 25);
    REQUIRE(springfield.Bart->GetCash() == 25);

    delete springfield.Homer;
    delete springfield.Marge;
    delete springfield.MrBurns;
    delete springfield.Lisa;
    delete springfield.Bart;
}

TEST_CASE("Marge buys from Apu", "[Marge]") {
    СBank bank(1000);
    Springfield springfield;
    springfield.Marge = new Marge(100, bank);
    springfield.Apu = new Apu(0, bank);

    springfield.Marge->OpenAccount();
    springfield.Apu->OpenAccount();

    springfield.Marge->DepositMoney(100);
    springfield.Marge->Act(springfield);

    REQUIRE(bank.GetAccountBalance(springfield.Apu->GetAccountId()) == 100);

    delete springfield.Marge;
    delete springfield.Apu;
}

TEST_CASE("Apu deposits and pays", "[Apu]") {
    СBank bank(1000);
    Springfield springfield;
    springfield.Apu = new Apu(300, bank);
    springfield.MrBurns = new MrBurns(0, bank);

    springfield.Apu->OpenAccount();
    springfield.MrBurns->OpenAccount();

    springfield.MrBurns->DepositMoney(2000);
    springfield.Apu->Act(springfield);

    REQUIRE(bank.GetAccountBalance(springfield.Apu->GetAccountId()) == 50);
    REQUIRE(bank.GetAccountBalance(springfield.MrBurns->GetAccountId()) == 250);

    delete springfield.Apu;
    delete springfield.MrBurns;
}

TEST_CASE("MrBurns pays employees", "[MrBurns]") {
    СBank bank(1000);
    Springfield springfield;
    springfield.MrBurns = new MrBurns(2000, bank);
    springfield.Homer = new Homer(0, bank);
    springfield.Smithers = new Smithers(0, bank);

    springfield.MrBurns->OpenAccount();
    springfield.Homer->OpenAccount();
    springfield.Smithers->OpenAccount();

    springfield.MrBurns->Act(springfield);

    REQUIRE(bank.GetAccountBalance(springfield.Homer->GetAccountId()) == 500);
    REQUIRE(bank.GetAccountBalance(springfield.Smithers->GetAccountId()) == 350);

    delete springfield.MrBurns;
    delete springfield.Homer;
    delete springfield.Smithers;
}

TEST_CASE("Snake steals from Homer", "[Snake]") {
    СBank bank(1000);
    Springfield springfield;
    springfield.Homer = new Homer(0, bank);
    springfield.Snake = new Snake(0, bank);

    springfield.Homer->OpenAccount();
    springfield.Snake->OpenAccount();
    bank.DepositMoney(springfield.Homer->GetAccountId(), 100);

    springfield.Snake->Act(springfield);

    REQUIRE(bank.GetAccountBalance(springfield.Homer->GetAccountId()) == 31);
    REQUIRE(bank.GetAccountBalance(springfield.Snake->GetAccountId()) == 69);

    delete springfield.Homer;
    delete springfield.Snake;
}

TEST_CASE("Smithers paranoid spending", "[Smithers]") {
    СBank bank(1000);
    Springfield springfield;
    springfield.Smithers = new Smithers(0, bank);
    springfield.Apu = new Apu(0, bank);

    springfield.Smithers->OpenAccount();
    springfield.Apu->OpenAccount();
    bank.DepositMoney(springfield.Smithers->GetAccountId(), 300);

    for (int i = 0; i < 3; ++i) {
        springfield.Smithers->Act(springfield);
    }

    REQUIRE(bank.GetAccountBalance(springfield.Smithers->GetAccountId()) == 50);

    delete springfield.Smithers;
    delete springfield.Apu;
}

TEST_CASE("Bart pays Apu in cash", "[Bart]") {
    Springfield springfield;
    springfield.Bart = new Bart(20);
    springfield.Lisa = new Lisa(10);
    springfield.Apu = new Apu(0, *(new СBank(1000)));

    springfield.Bart->Act(springfield);
    springfield.Lisa->Act(springfield);

    REQUIRE(springfield.Bart->GetCash() == 3);
    REQUIRE(springfield.Lisa->GetCash() == 1);
    REQUIRE(springfield.Apu->GetCash() == 26);

    delete springfield.Apu;
    delete springfield.Lisa;
    delete springfield.Bart;
}

TEST_CASE("Nelson steals and buys", "[Nelson]") {
    Springfield springfield;
    springfield.Bart = new Bart(20);
    springfield.Apu = new Apu(0, *(new СBank(1000)));
    springfield.Nelson = new Nelson(0);

    springfield.Nelson->Act(springfield);

    REQUIRE(springfield.Apu->GetCash() == 15);

    delete springfield.Bart;
    delete springfield.Apu;
    delete springfield.Nelson;
}
