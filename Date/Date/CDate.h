#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <optional>
#include <tuple>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
    CDate() : m_days(0) {}
    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    ~CDate() = default;

    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;
    bool IsValid() const;

    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);

    CDate& operator++();
    CDate operator++(int);
    CDate& operator--();
    CDate operator--(int);
    CDate operator+(int days) const;
    CDate operator-(int days) const;
    int operator-(const CDate& other) const;
    CDate& operator+=(int days);
    CDate& operator-=(int days);
    bool operator==(const CDate& other) const;
    bool operator!=(const CDate& other) const;
    bool operator<(const CDate& other) const;
    bool operator<=(const CDate& other) const;
    bool operator>(const CDate& other) const;
    bool operator>=(const CDate& other) const;

private:
    static constexpr unsigned MIN_YEAR = 1970;
    static constexpr unsigned MAX_YEAR = 9999;
    static constexpr unsigned MAX_DAYS = 2932896;

    std::optional<unsigned> m_days = 0;

    static bool IsLeapYear(unsigned year);
    static unsigned GetDaysInMonth(unsigned month, unsigned year);
    static unsigned DateToDays(unsigned d, unsigned m, unsigned y);
    std::tuple<unsigned, unsigned, unsigned> GetDMY() const;
};
