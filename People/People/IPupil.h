#pragma once
#include "IPerson.h"

class IPupil : public IPerson {
public:
    virtual std::string GetSchoolName() const = 0;
    virtual std::string GetSchoolClass() const = 0;
};