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

    unsigned yearDiff = y - MIN_YEAR;

    unsigned leapYears = (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400
        - (MIN_YEAR - 1) / 4 + (MIN_YEAR - 1) / 100 - (MIN_YEAR - 1) / 400;

    unsigned daysFromYears = yearDiff * 365 + leapYears;

    unsigned daysFromMonths = 0;
    for (unsigned i = 1; i < m; ++i)
    {
        daysFromMonths += GetDaysInMonth(i, y);
    }

    return daysFromYears + daysFromMonths + (d - 1);
}


std::tuple<unsigned, unsigned, unsigned> CDate::GetDMY() const
{
    if (!IsValid()) return { 0, 0, 0 };

    unsigned days = m_days.value();

    unsigned y = MIN_YEAR + days / 365;

    while (true)
    {
        unsigned yearDays = IsLeapYear(y) ? 366 : 365;
        unsigned daysUpToYear = DateToDays(1, 1, y);
        if (days < daysUpToYear)
        {
            --y;
            break;
        }
        if (days < daysUpToYear + yearDays)
        {
            break;
        }
        ++y;
    }

    unsigned daysInYear = days - DateToDays(1, 1, y);

    unsigned m = 1;
    while (true)
    {
        unsigned monthDays = GetDaysInMonth(m, y);
        if (daysInYear < monthDays) break;
        daysInYear -= monthDays;
        ++m;
    }

    unsigned d = daysInYear + 1;

    return { d, m, y };
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
