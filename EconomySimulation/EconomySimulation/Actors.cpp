#include <iostream>
#include <vector>
#include "Bank.h"
#include "Homer.h"
#include "Marge.h"
#include "BartLisa.h"
#include "Burns.h"
#include "Apu.h"

class Actor {
public:
    virtual ~Actor() = default;
    virtual void Act(Bank& bank) = 0;
};

class Homer : public Actor {
public:
    Homer(AccountId account, AccountId margeAccount, AccountId powerCompanyAccount, AccountId bart, AccountId lisa)
        : account(account), margeAccount(margeAccount), powerCompanyAccount(powerCompanyAccount), bart(bart), lisa(lisa) {}

    void Act(Bank& bank) override {
        // Перевод денег жене
        if (bank.TrySendMoney(account, margeAccount, 50)) {
            std::cout << "Homer sent 50 to Marge\n";
        }
        // Оплата электричества
        if (bank.TrySendMoney(account, powerCompanyAccount, 30)) {
            std::cout << "Homer paid 30 for electricity\n";
        }
        // Снятие наличных для детей
        if (bank.TryWithdrawMoney(account, 20)) {
            std::cout << "Homer withdrew 20 for kids\n";
        }
    }

private:
    AccountId account, margeAccount, powerCompanyAccount, bart, lisa;
};

class Marge : public Actor {
public:
    Marge(AccountId account, AccountId apuAccount) : account(account), apuAccount(apuAccount) {}
    void Act(Bank& bank) override {
        if (bank.TrySendMoney(account, apuAccount, 40)) {
            std::cout << "Marge bought groceries from Apu\n";
        }
    }
private:
    AccountId account, apuAccount;
};

class BartLisa : public Actor {
public:
    BartLisa(AccountId cash, AccountId apuAccount) : cash(cash), apuAccount(apuAccount) {}
    void Act(Bank& bank) override {
        if (cash >= 10) {
            cash -= 10;
            std::cout << "Bart/Lisa bought small items from Apu\n";
        }
    }
private:
    Money cash;
    AccountId apuAccount;
};

class Apu : public Actor {
public:
    Apu(AccountId account, AccountId powerCompanyAccount) : account(account), powerCompanyAccount(powerCompanyAccount) {}
    void Act(Bank& bank) override {
        if (bank.TrySendMoney(account, powerCompanyAccount, 20)) {
            std::cout << "Apu paid for electricity\n";
        }
    }
private:
    AccountId account, powerCompanyAccount;
};

class Burns : public Actor {
public:
    Burns(AccountId account, AccountId homerAccount) : account(account), homerAccount(homerAccount) {}
    void Act(Bank& bank) override {
        if (bank.TrySendMoney(account, homerAccount, 100)) {
            std::cout << "Burns paid salary to Homer\n";
        }
    }
private:
    AccountId account, homerAccount;
};
