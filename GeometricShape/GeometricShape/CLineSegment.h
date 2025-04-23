#pragma once
#include "CShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

class CLineSegment : public CShape
{
public:
    CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;

    void Draw(ICanvas& canvas) const;

private:
    CPoint m_start;
    CPoint m_end;
};