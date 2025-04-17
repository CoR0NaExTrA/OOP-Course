#include "CDate.h"

bool CDate::IsLeapYear(unsigned year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned CDate::GetDaysInMonth(unsigned month, unsigned year)
{
    static constexpr unsigned days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && IsLeapYear(year)) return 29;
    return days[month - 1];
}

unsigned CDate::DateToDays(unsigned d, unsigned m, unsigned y)
{
    if (y < MIN_YEAR || y > MAX_YEAR || m < 1 || m > 12 || d < 1 || d > GetDaysInMonth(m, y))
    {
        return MAX_DAYS;
    }
    unsigned days = 0;
    for (unsigned year = MIN_YEAR; year < y; ++year)
    {
        days += IsLeapYear(year) ? 366 : 365;
    }
    for (unsigned month = 1; month < m; ++month)
    {
        days += GetDaysInMonth(month, y);
    }
    days += d - 1;
    return days;
}

std::tuple<unsigned, unsigned, unsigned> CDate::GetDMY() const
{
    if (!IsValid()) return { 0, 0, 0 };

    unsigned days = m_days.value();
    unsigned y = MIN_YEAR;
    while (true)
    {
        unsigned yearDays = IsLeapYear(y) ? 366 : 365;
        if (days < yearDays) break;
        days -= yearDays;
        ++y;
    }
    unsigned m = 1;
    while (true)
    {
        unsigned monthDays = GetDaysInMonth(m, y);
        if (days < monthDays) break;
        days -= monthDays;
        ++m;
    }
    return { days + 1, m, y };
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
    m_days = DateToDays(day, static_cast<unsigned>(month), year);
    if (m_days >= MAX_DAYS)
        m_days = std::nullopt;
}

CDate::CDate(unsigned timestamp)
{
    if (timestamp >= MAX_DAYS)
    {
        m_days = std::nullopt;
    }
    else
    {
        m_days = timestamp;
    }
}

unsigned CDate::GetDay() const
{
    auto [d, m, y] = GetDMY();
    return d;
}

Month CDate::GetMonth() const
{
    auto [d, m, y] = GetDMY();
    return static_cast<Month>(m);
}

unsigned CDate::GetYear() const
{
    auto [d, m, y] = GetDMY();
    return y;
}

WeekDay CDate::GetWeekDay() const
{
    return static_cast<WeekDay>((m_days.value() + 4) % 7);
}

bool CDate::IsValid() const
{
    return m_days.has_value();
}
