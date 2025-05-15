#pragma once
#include "IWorker.h"
#include "CPersonImpl.h"

class CWorker : public CPersonImpl<IWorker> {
public:
    void SetSpecialty(const std::string& specialty) { m_specialty = specialty; }
    std::string GetSpecialty() const override { return m_specialty; }

private:
    std::string m_specialty;
};