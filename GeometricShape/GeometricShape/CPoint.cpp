#include "CPoint.h"
#include <sstream>

std::string CPoint::ToString() const
{
    std::ostringstream oss;
    oss << "(" << m_x << ", " << m_y << ")";
    return oss.str();
}