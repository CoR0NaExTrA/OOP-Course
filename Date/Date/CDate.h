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

    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;
    bool IsValid() const;

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
