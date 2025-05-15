#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base> {
public:
    void SetUniversityName(const std::string& name) { m_university = name; }
    void SetStudentID(const std::string& id) { m_studentID = id; }

    std::string GetUniversityName() const override { return m_university; }
    std::string GetStudentID() const override { return m_studentID; }

private:
    std::string m_university;
    std::string m_studentID;
};