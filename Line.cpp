#include "PrecompiledHeaders.h"

#include "Line.h"
#include "Point.h"

Point Line::Project(Point const & point) const
{
    // Distance from m_B is ( point - m_B ) dot m_M

    return m_B + m_M * Dot((point.value_ - m_B), m_M);
}

Point Ray::Project(Point const & point) const
{
    // Distance from m_B is ( point - m_B ) dot m_M

    return m_B + m_M * Dot((point.value_ - m_B), m_M);
}

Point Segment::Project(Point const & point) const
{
    // Distance from m_B is ( ( point - m_B ) dot m_M ) / ||m_M||

    return m_B + m_M * (Dot((point.value_ - m_B), m_M) / m_M.Length2());
}
