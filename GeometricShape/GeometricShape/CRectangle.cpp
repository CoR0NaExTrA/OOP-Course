#include "CRectangle.h"
#include <sstream>

CRectangle::CRectangle(const CPoint& leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
    : m_leftTop(leftTop), m_width(width), m_height(height), m_outlineColor(outlineColor), m_fillColor(fillColor)
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

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
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