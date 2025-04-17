#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
    : m_window(window)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
    sf::Vertex line[] =
    {
        sf::Vertex({ static_cast<float>(from.x), static_cast<float>(from.y) }, sf::Color(lineColor)),
        sf::Vertex({ static_cast<float>(to.x), static_cast<float>(to.y) }, sf::Color(lineColor))
    };
    m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
    }
    polygon.setFillColor(sf::Color(fillColor));
    m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.x - radius), static_cast<float>(center.y - radius));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color(lineColor));
    circle.setOutlineThickness(1.f);
    m_window.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.x - radius), static_cast<float>(center.y - radius));
    circle.setFillColor(sf::Color(fillColor));
    m_window.draw(circle);
}
