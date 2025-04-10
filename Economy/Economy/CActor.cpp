#include "CActor.h"

CActor::CActor(Money cash)
{
	if (cash < 0)
	{
		throw std::out_of_range("Amount cannot be negative");
	}
	m_cash = cash;
}

Money CActor::GetCash() const
{
	return m_cash;
}

bool CActor::SendCash(CActor& recipient, Money amount)
{
	if (m_cash < amount)
	{
		return false;
	}

	m_cash -= amount;
	recipient.AddCash(amount);
	return true;
}

bool CActor::Steal(CActor& victim, Money amount)
{
	return victim.SendCash(*this, amount);
}

void CActor::AddCash(Money cash)
{
	m_cash += cash;
}

bool CActor::SpendCash(Money cash)
{
	if (m_cash < cash)
	{
		return false;
	}

	m_cash -= cash;
	return true;
}

Money CActorBank::GetAccountBalance() const
{
	return bank.GetAccountBalance(accountId);
}

AccountId CActorBank::GetAccountId() const
{
	return accountId;
}

bool CActorBank::SendMoney(AccountId dstAccountId, Money amount)
{
	return bank.TrySendMoney(accountId, dstAccountId, amount);
}

bool CActorBank::StealMoney(AccountId victimAccountId, Money amount)
{
	return bank.TrySendMoney(victimAccountId, accountId, amount);
}

bool CActorBank::WithdrawMoney(Money amount)
{
	if (!bank.TryWithdrawMoney(accountId, amount))
	{
		return false;
	}

	AddCash(amount);
	return true;
}

bool CActorBank::DepositMoney(Money amount)
{
	if (!SpendCash(amount))
	{
		return false;
	}

	bank.DepositMoney(accountId, amount);
	return true;
}

Money CActorBank::CloseAccount()
{
	Money balance = bank.CloseAccount(accountId);
	AddCash(balance);
	return balance;
}

void CActorBank::OpenAccount()
{
	accountId = bank.OpenAccount();
}