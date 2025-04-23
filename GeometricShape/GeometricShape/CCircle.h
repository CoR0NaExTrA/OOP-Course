#pragma once
#include "CSolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

const double M_PI = 3.14;

class CCircle : public CSolidShape
{
public:
    CCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CPoint GetCenter() const;
    double GetRadius() const;

    void Draw(ICanvas& canvas) const;

private:
    CPoint m_center;
    double m_radius;
};