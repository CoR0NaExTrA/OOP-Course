#pragma once
#include <string>

template <typename Base>
class CPersonImpl : public Base {
public:
    void SetFirstName(const std::string& firstName) { m_firstName = firstName; }
    void SetLastName(const std::string& lastName) { m_lastName = lastName; }
    void SetPatronymic(const std::string& patronymic) { m_patronymic = patronymic; }
    void SetAddress(const std::string& address) { m_address = address; }

    std::string GetFirstName() const override { return m_firstName; }
    std::string GetLastName() const override { return m_lastName; }
    std::string GetPatronymic() const override { return m_patronymic; }
    std::string GetAddress() const override { return m_address; }

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_patronymic;
    std::string m_address;
};