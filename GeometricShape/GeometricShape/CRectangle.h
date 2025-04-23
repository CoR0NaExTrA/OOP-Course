#pragma once
#include "CSolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

class CRectangle : public CSolidShape
{
public:
    CRectangle(const CPoint& leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CPoint GetLeftTop() const;
    double GetWidth() const;
    double GetHeight() const;

    void Draw(ICanvas& canvas) const;

private:
    CPoint m_leftTop;
    double m_width;
    double m_height;
};
