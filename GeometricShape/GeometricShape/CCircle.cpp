#include "CCircle.h"
#include <cmath>
#include <sstream>

CCircle::CCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor)
    : CSolidShape(outlineColor, fillColor), m_center(center), m_radius(radius)
{
}

double CCircle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
    std::ostringstream oss;
    oss << "Circle: center=" << m_center.ToString()
        << ", radius=" << m_radius
        << ", OutlineColor=#" << std::hex << m_outlineColor
        << ", FillColor=#" << std::hex << m_fillColor;
    return oss.str();
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}

void CCircle::Draw(ICanvas& canvas) const
{
    canvas.FillCircle(m_center, m_radius, m_fillColor);
    canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}

