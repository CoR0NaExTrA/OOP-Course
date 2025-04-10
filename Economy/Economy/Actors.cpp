#include "../Economy/Actors.h"


void Homer::Act(Springfield& springfield)
{
	if (SendMoney(springfield.Marge->GetAccountId(), 100))
	{
		std::cout << "Homer sent  to Marge`s card\n";
	}

	if (SendMoney(springfield.MrBurns->GetAccountId(), 250))
	{
		std::cout << "Homer paid  for electricity\n";
	}

	if (WithdrawMoney(50))
	{
		if (SendCash(*springfield.Lisa, 25))
		{
			std::cout << "Homer gave cash to Lisa\n";
		}

		if (SendCash(*springfield.Bart, 25))
		{
			std::cout << "Homer gave cash to Bart\n";
		}
	}
}

void Marge::Act(Springfield& springfield)
{
	if (SendMoney(springfield.Apu->GetAccountId(), 100))
	{
		std::cout << "Marge bought products from Apu\n";
	}
}

void Apu::Act(Springfield& springfield)
{
	if (GetCash() > 0)
	{
		if (DepositMoney(GetCash()))
		{
			std::cout << "Apu deposited cash to his bank account\n";
		}
	}

	if (SendMoney(springfield.MrBurns->GetAccountId(), 250))
	{
		std::cout << "Apu paid for electricity\n";
	}
}

void MrBurns::Act(Springfield& springfield)
{
	if (SendMoney(springfield.Homer->GetAccountId(), 500))
	{
		std::cout << "Mr. Burns paid Homer for his work\n";
	}

	if (SendMoney(springfield.Smithers->GetAccountId(), 350))
	{
		std::cout << "Mr. Burns paid Smithers for his work\n";
	}
}

void Snake::Act(Springfield& springfield)
{
	if (StealMoney(springfield.Homer->GetAccountId(), 69))
	{
		std::cout << "Snake stole money from Homer's bank account\n";
	}
}

void Smithers::Act(Springfield& springfield)
{
	if (SendMoney(springfield.Apu->GetAccountId(), 250))
	{
		std::cout << "Smithers paid for Apu's products\n";
	}

	m_paranoia++;
	if (m_paranoia >= m_paranoia_border)
	{
		m_paranoia = 0;
		Money cash = CloseAccount();
		std::cout << "Smithers closed his bank account\n";

		OpenAccount();
		if (DepositMoney(cash))
		{
			std::cout << "Smithers opened new bank account and put cash\n";
		}
	}
}

void Bart::Act(Springfield& springfield)
{
	if (SendCash(*springfield.Apu, 17))
	{
		std::cout << "Bart spend some cash in Apu`s shop\n";
	}
}

void Lisa::Act(Springfield& springfield)
{
	if (SendCash(*springfield.Apu, 9))
	{
		std::cout << "Lisa spend some cash in Apu`s shop\n";
	}
}

void Nelson::Act(Springfield& springfield)
{
	int cashToSteal = 1 + (std::rand() % 20);
	if (Steal(*springfield.Bart, cashToSteal))
	{
		std::cout << "Nelson stole cash from Bart\n";
	}

	if (SendCash(*springfield.Apu, 15))
	{
		std::cout << "Nelson bought cigaretes from Apu\n";
	}
}