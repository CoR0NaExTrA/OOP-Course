#include "CTriangle.h"
#include <cmath>
#include <sstream>

namespace
{
    double Distance(const CPoint& a, const CPoint& b)
    {
        double dx = a.GetX() - b.GetX();
        double dy = a.GetY() - b.GetY();
        return std::sqrt(dx * dx + dy * dy);
    }
}

CTriangle::CTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3, uint32_t outlineColor, uint32_t fillColor)
    : m_v1(v1), m_v2(v2), m_v3(v3), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
    double a = Distance(m_v1, m_v2);
    double b = Distance(m_v2, m_v3);
    double c = Distance(m_v3, m_v1);
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double CTriangle::GetPerimeter() const
{
    return Distance(m_v1, m_v2) + Distance(m_v2, m_v3) + Distance(m_v3, m_v1);
}

std::string CTriangle::ToString() const
{
    std::ostringstream oss;
    oss << "Triangle: V1=" << m_v1.ToString()
        << ", V2=" << m_v2.ToString()
        << ", V3=" << m_v3.ToString()
        << ", OutlineColor=#" << std::hex << m_outlineColor
        << ", FillColor=#" << std::hex << m_fillColor;
    return oss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_v1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_v2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_v3;
}