#include "CShapeManager.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

#include <sstream>
#include <iostream>
#include <algorithm>

void CShapeManager::AddShapeFromString(const std::string& line)
{
    if (auto shape = ParseShape(line))
    {
        m_shapes.push_back(shape);
    }
}

void CShapeManager::PrintInfoAboutExtremes() const
{
    if (m_shapes.empty())
    {
        std::cout << "No shapes were parsed.\n";
        return;
    }

    auto maxAreaShape = GetMaxAreaShape();
    auto minPerimeterShape = GetMinPerimeterShape();

    PrintShapeDetails("Shape with maximum area", maxAreaShape);
    PrintShapeDetails("Shape with minimum perimeter", minPerimeterShape);
}

std::shared_ptr<IShape> CShapeManager::ParseShape(const std::string& line) const
{
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "line")
    {
        double x1, y1, x2, y2;
        std::string color;
        iss >> x1 >> y1 >> x2 >> y2 >> color;
        return std::make_shared<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), std::stoul(color, nullptr, 16));
    }
    else if (type == "triangle")
    {
        double x1, y1, x2, y2, x3, y3;
        std::string outline, fill;
        iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outline >> fill;
        return std::make_shared<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3),
            std::stoul(outline, nullptr, 16), std::stoul(fill, nullptr, 16));
    }
    else if (type == "rectangle")
    {
        double x, y, w, h;
        std::string outline, fill;
        iss >> x >> y >> w >> h >> outline >> fill;
        return std::make_shared<CRectangle>(CPoint(x, y), w, h,
            std::stoul(outline, nullptr, 16), std::stoul(fill, nullptr, 16));
    }
    else if (type == "circle")
    {
        double x, y, r;
        std::string outline, fill;
        iss >> x >> y >> r >> outline >> fill;
        return std::make_shared<CCircle>(CPoint(x, y), r,
            std::stoul(outline, nullptr, 16), std::stoul(fill, nullptr, 16));
    }

    return nullptr;
}

std::shared_ptr<IShape> CShapeManager::GetMaxAreaShape() const
{
    return *std::max_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetArea() < b->GetArea();
        });
}

std::shared_ptr<IShape> CShapeManager::GetMinPerimeterShape() const
{
    return *std::min_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetPerimeter() < b->GetPerimeter();
        });
}

void CShapeManager::PrintShapeDetails(const std::string& title, const std::shared_ptr<IShape>& shape) const
{
    std::cout << "\n" << title << ":\n";
    std::cout << shape->ToString() << "\n";
    std::cout << "Perimeter: " << shape->GetPerimeter() << "\n";
    std::cout << "Area: " << shape->GetArea() << "\n";
    std::cout << "Outline color: #" << std::hex << shape->GetOutlineColor() << std::dec << "\n";

    if (auto solid = std::dynamic_pointer_cast<ISolidShape>(shape))
    {
        std::cout << "Fill color: #" << std::hex << solid->GetFillColor() << std::dec << "\n";
    }
}

void CShapeManager::DrawShapes(CCanvas& canvas)
{
    for (auto& shape : m_shapes)
    {
        if (auto drawable = std::dynamic_pointer_cast<ICanvasDrawable>(shape))
        {
            drawable->Draw(canvas);
        }
    }
}