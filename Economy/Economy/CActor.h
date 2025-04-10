#pragma once
#include "../Economy/CBank.h"

struct Springfield;

class CActor
{
public:
	explicit CActor(Money cash);

	[[nodiscard]] Money GetCash() const;
	[[nodiscard]] bool SendCash(CActor& recipient, Money amount);
	[[nodiscard]] bool Steal(CActor& victim, Money amount);

	virtual void Act(Springfield& springfield) = 0;
	virtual ~CActor() = default;

protected:
	void AddCash(Money cash);
	bool SpendCash(Money cash);

private:
	Money m_cash;

};

class CActorBank : public CActor
{
public:
	CActorBank(Money cash, Bank& bank)
		: bank(bank), CActor(cash)
	{
		accountId = bank.OpenAccount();
	}

	[[nodiscard]] Money GetAccountBalance() const;
	[[nodiscard]] AccountId GetAccountId() const;
	[[nodiscard]] bool SendMoney(AccountId dstAccountId, Money amount);
	[[nodiscard]] bool StealMoney(AccountId victimAccountId, Money amount);
	[[nodiscard]] bool WithdrawMoney(Money amount);
	bool DepositMoney(Money amount);
	[[nodiscard]] Money CloseAccount();
	void OpenAccount();

private:
	AccountId accountId;
	Bank& bank;
};

struct Springfield
{
	CActorBank* Homer;
	CActorBank* Marge;
	CActor* Bart;
	CActor* Lisa;
	CActorBank* Apu;
	CActorBank* MrBurns;
	CActor* Nelson;
	CActorBank* Snake;
	CActorBank* Smithers;
};