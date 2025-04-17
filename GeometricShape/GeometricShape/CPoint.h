#pragma once
#include <string>

class CPoint
{
public:
    CPoint(double x, double y)
        : m_x(x), m_y(y) {}

    double GetX() const { return m_x; }
    double GetY() const { return m_y; }

    std::string ToString() const;

private:
    double m_x;
    double m_y;
};