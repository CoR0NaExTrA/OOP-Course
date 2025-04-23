#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
    : m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor)
{
    sf::Vertex line[] =
    {
        sf::Vertex({ static_cast<float>(from.GetX()), static_cast<float>(from.GetY()) }, ConvertColor(lineColor)),
        sf::Vertex({ static_cast<float>(to.GetX()), static_cast<float>(to.GetY()) }, ConvertColor(lineColor))
    };
    m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].GetX()), static_cast<float>(points[i].GetY())));
    }
    polygon.setFillColor(ConvertColor(fillColor));
    m_window.draw(polygon);
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t lineColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.GetX() - radius), static_cast<float>(center.GetY() - radius));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(ConvertColor(lineColor));
    circle.setOutlineThickness(1.f);
    m_window.draw(circle);
}

void CCanvas::FillCircle(const CPoint& center, double radius, uint32_t fillColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.GetX() - radius), static_cast<float>(center.GetY() - radius));
    circle.setFillColor(ConvertColor(fillColor));
    m_window.draw(circle);
}

sf::Color CCanvas::ConvertColor(uint32_t color)
{
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    return sf::Color(r, g, b);
}
