#pragma once
#include <vector>
#include <string>
#include <memory>
#include "IShape.h"
#include "CCanvas.h"

class CShapeManager
{
public:
    void AddShapeFromString(const std::string& line);
    void PrintInfoAboutExtremes() const;
    void DrawShapes(CCanvas& canvas);

private:
    std::shared_ptr<IShape> ParseShape(const std::string& line) const;
    std::shared_ptr<IShape> GetMaxAreaShape() const;
    std::shared_ptr<IShape> GetMinPerimeterShape() const;
    void PrintShapeDetails(const std::string& title, const std::shared_ptr<IShape>& shape) const;

    std::vector<std::shared_ptr<IShape>> m_shapes;
};
