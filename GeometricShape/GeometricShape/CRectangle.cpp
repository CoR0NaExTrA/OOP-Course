#include "CRectangle.h"
#include <sstream>

CRectangle::CRectangle(const CPoint& leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
    : CSolidShape(outlineColor, fillColor), m_leftTop(leftTop), m_width(width), m_height(height)
{
}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
    std::ostringstream oss;
    oss << "Rectangle: leftTop=" << m_leftTop.ToString()
        << ", width=" << m_width << ", height=" << m_height
        << ", OutlineColor=#" << std::hex << m_outlineColor
        << ", FillColor=#" << std::hex << m_fillColor;
    return oss.str();
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
    CPoint topLeft = m_leftTop;
    CPoint topRight = { m_leftTop.GetX() + m_width, m_leftTop.GetY() };
    CPoint bottomLeft = { m_leftTop.GetX(), m_leftTop.GetY() + m_height };
    CPoint bottomRight = { m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height };

    canvas.FillPolygon({ topLeft, topRight, bottomRight, bottomLeft }, m_fillColor);
    canvas.DrawLine(topLeft, topRight, m_outlineColor);
    canvas.DrawLine(topRight, bottomRight, m_outlineColor);
    canvas.DrawLine(bottomRight, bottomLeft, m_outlineColor);
    canvas.DrawLine(bottomLeft, topLeft, m_outlineColor);
}
