#pragma once
#include "IAdvancedStudent.h"
#include "CStudentImpl.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent> {
public:
    void SetThesisTopic(const std::string& topic) { m_topic = topic; }
    std::string GetThesisTopic() const override { return m_topic; }

private:
    std::string m_topic;
};
