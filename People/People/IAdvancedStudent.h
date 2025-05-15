#pragma once
#include "IStudent.h"

class IAdvancedStudent : public IStudent {
public:
    virtual std::string GetThesisTopic() const = 0;
};
