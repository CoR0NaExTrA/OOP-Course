#include "CLineSegment.h"
#include <cmath>
#include <sstream>

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor)
    : m_start(start), m_end(end), m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    double dx = m_end.GetX() - m_start.GetX();
    double dy = m_end.GetY() - m_start.GetY();
    return std::sqrt(dx * dx + dy * dy);
}

std::string CLineSegment::ToString() const
{
    std::ostringstream oss;
    oss << "LineSegment: start=" << m_start.ToString()
        << ", end=" << m_end.ToString()
        << ", color=#" << std::hex << m_outlineColor;
    return oss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_end;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_start, m_end, m_outlineColor);
}
