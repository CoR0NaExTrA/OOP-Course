#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
    CSolidShape(uint32_t outlineColor, uint32_t fillColor)
        : m_outlineColor(outlineColor), m_fillColor(fillColor)
    {
    }

    uint32_t GetOutlineColor() const override
    {
        return m_outlineColor;
    }

    uint32_t GetFillColor() const override
    {
        return m_fillColor;
    }

protected:
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};
