#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
    explicit CShape(uint32_t outlineColor)
        : m_outlineColor(outlineColor)
    {
    }

    uint32_t GetOutlineColor() const
    {
        return m_outlineColor;
    }

protected:
    uint32_t m_outlineColor;
};
