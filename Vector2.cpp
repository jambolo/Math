/** @file *//********************************************************************************************************

                                                     Vector2.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Vector2.cpp#9 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Vector2.h"

#include "Matrix22.h"

Vector2 const & Vector2::Transform(Matrix22 const & m)
{
    float const x = m_X;
    float const y = m_Y;

    m_X = x * m.m_Xx + y * m.m_Yx;
    m_Y = x * m.m_Xy + y * m.m_Yy;

    return *this;
}

Vector2 const & Vector2::Rotate(float angle)
{
    float const c = cosf(angle);
    float const s = sinf(angle);

    float const x = m_X;
    float const y = m_Y;

    m_X = x * c - y * s;
    m_Y = x * s + y * c;

    return *this;
}
