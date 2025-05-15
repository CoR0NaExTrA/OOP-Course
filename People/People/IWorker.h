#pragma once
#include "IPerson.h"

class IWorker : public IPerson {
public:
    virtual std::string GetSpecialty() const = 0;
};