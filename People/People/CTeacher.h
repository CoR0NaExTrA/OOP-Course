#pragma once
#include "ITeacher.h"
#include "CPersonImpl.h"

class CTeacher : public CPersonImpl<ITeacher> {
public:
    void SetSubjectName(const std::string& subject) { m_subject = subject; }
    std::string GetSubjectName() const override { return m_subject; }

private:
    std::string m_subject;
};