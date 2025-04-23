#pragma once
#include "CSolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

class CTriangle : public CSolidShape
{
public:
    CTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3, uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

    void Draw(ICanvas& canvas) const;

private:
    CPoint m_v1, m_v2, m_v3;
};