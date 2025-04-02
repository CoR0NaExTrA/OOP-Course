#pragma once
#include "Actor.h"

class Marge : public Actor {
public:
    explicit Marge(Bank& bank);

    void Act() override;
};