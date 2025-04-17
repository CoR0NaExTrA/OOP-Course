#pragma once
#include <vector>
#include "CPoint.h"

class ICanvas
{
public:
    virtual void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) = 0;
    virtual void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) = 0;
    virtual void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) = 0;
    virtual void FillCircle(const CPoint& center, double radius, uint32_t fillColor) = 0;

    virtual ~ICanvas() = default;
};
