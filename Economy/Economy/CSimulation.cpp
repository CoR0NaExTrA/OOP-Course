#include "CSimulation.h"

CSimulation::CSimulation()
{
	m_bank = std::make_unique<ÑBank>(m_initialCash);

	m_homer = std::make_unique<Homer>(2500, *m_bank);
	m_marge = std::make_unique<Marge>(1000, *m_bank);
	m_bart = std::make_unique<Bart>(50);
	m_lisa = std::make_unique<Lisa>(50);
	m_apu = std::make_unique<Apu>(5000, *m_bank);
	m_mrBurns = std::make_unique<MrBurns>(50000, *m_bank);
	m_nelson = std::make_unique<Nelson>(100);
	m_snake = std::make_unique<Snake>(250, *m_bank);
	m_smithers = std::make_unique<Smithers>(9000, *m_bank);

	m_springfield.Homer = m_homer.get();
	m_springfield.Marge = m_marge.get();
	m_springfield.Bart = m_bart.get();
	m_springfield.Lisa = m_lisa.get();
	m_springfield.Apu = m_apu.get();
	m_springfield.MrBurns = m_mrBurns.get();
	m_springfield.Nelson = m_nelson.get();
	m_springfield.Snake = m_snake.get();
	m_springfield.Smithers = m_smithers.get();
}

void CSimulation::RunSimulation(int iterations)
{
	for (int i = 0; i < iterations; ++i)
	{
		m_homer->Act(m_springfield);
		m_marge->Act(m_springfield);
		m_bart->Act(m_springfield);
		m_lisa->Act(m_springfield);
		m_apu->Act(m_springfield);
		m_mrBurns->Act(m_springfield);
		m_nelson->Act(m_springfield);
		m_snake->Act(m_springfield);
		m_smithers->Act(m_springfield);

		std::cout << "\n";
	}

	if (IsAgreedState())
	{
		std::cout << "Simulation is in agreed state\n";
	}
	else
	{
		std::cout << "Simulation is NOT in agreed state\n";
	}
}

bool CSimulation::IsAgreedState() const
{
	const Money bankBalance = m_bank->GetCash();

	const Money totalCharacterCash =
		m_homer->GetCash() +
		m_marge->GetCash() +
		m_bart->GetCash() +
		m_lisa->GetCash() +
		m_apu->GetCash() +
		m_mrBurns->GetCash() +
		m_nelson->GetCash() +
		m_snake->GetCash() +
		m_smithers->GetCash();


	const Money totalCharacterBalance =
		m_homer->GetAccountBalance() +
		m_marge->GetAccountBalance() +
		m_apu->GetAccountBalance() +
		m_mrBurns->GetAccountBalance() +
		m_snake->GetAccountBalance() +
		m_smithers->GetAccountBalance();

	const Money totalMoney = totalCharacterBalance + totalCharacterCash;

	std::cout << "\nStats: \n"
		<< "Bank Balance = " << bankBalance << "\n"
		<< "Character cash = " << totalCharacterCash << "\n"
		<< "Character Balance = " << totalCharacterBalance << "\n"
		<< "Total Money = " << totalMoney << "\n"
		<< "Initital = " << m_initialCash << "\n";

	return totalMoney == m_initialCash;
}