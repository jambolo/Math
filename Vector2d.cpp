#include "PrecompiledHeaders.h"

#include "Vector2d.h"

#include "Matrix22d.h"

Vector2d const & Vector2d::Transform(Matrix22d const & m)
{
    double const x = m_X;
    double const y = m_Y;

    m_X = x * m.m_Xx + y * m.m_Yx;
    m_Y = x * m.m_Xy + y * m.m_Yy;

    return *this;
}

Vector2d const & Vector2d::Rotate(double angle)
{
    double const c = cos(angle);
    double const s = sin(angle);

    double const x = m_X;
    double const y = m_Y;

    m_X = x * c - y * s;
    m_Y = x * s + y * c;

    return *this;
}
