#pragma once
#include "IPupil.h"
#include "CPersonImpl.h"

class CPupil : public CPersonImpl<IPupil> {
public:
    void SetSchoolName(const std::string& name) { m_schoolName = name; }
    void SetSchoolClass(const std::string& schoolClass) { m_schoolClass = schoolClass; }

    std::string GetSchoolName() const override { return m_schoolName; }
    std::string GetSchoolClass() const override { return m_schoolClass; }

private:
    std::string m_schoolName;
    std::string m_schoolClass;
};