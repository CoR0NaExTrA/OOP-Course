#pragma once
#include "../Economy/CActor.h"
#include <iostream>

class Homer : public CActorBank
{
public:
	explicit Homer(Money cash, Bank& bank)
		: CActorBank(cash, bank) {}

	void Act(Springfield& springfield) override;
};

class Marge : public CActorBank
{
public:
    explicit Marge(Money cash, Bank& bank)
        : CActorBank(cash, bank) {}

    void Act(Springfield& springfield) override;
};

class Apu : public CActorBank
{
public:
    explicit Apu(Money cash, Bank& bank)
        : CActorBank(cash, bank) {}

    void Act(Springfield& springfield) override;
};

class MrBurns : public CActorBank
{
public:
    explicit MrBurns(Money cash, Bank& bank)
        : CActorBank(cash, bank) {}

    void Act(Springfield& springfield) override;
};

class Snake : public CActorBank
{
public:
    explicit Snake(Money cash, Bank& bank)
        : CActorBank(cash, bank) {}

    void Act(Springfield& springfield) override;
};

class Smithers : public CActorBank
{
public:
    explicit Smithers(Money cash, Bank& bank)
        : CActorBank(cash, bank) {}

    void Act(Springfield& springfield) override;

private:
    int m_paranoia = 0;
    const int m_paranoia_border = 3;
};

class Bart : public CActor
{
public:
    explicit Bart(Money cash)
        : CActor(cash) {}

    void Act(Springfield& springfield) override;
};

class Lisa : public CActor
{
public:
    explicit Lisa(Money cash)
        : CActor(cash) {}

    void Act(Springfield& springfield) override;
};

class Nelson : public CActor
{
public:
    explicit Nelson(Money cash)
        : CActor(cash) {}

    void Act(Springfield& springfield) override;
};