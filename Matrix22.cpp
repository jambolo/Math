/** @file *//********************************************************************************************************

                                                    Matrix22.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Matrix22.cpp#11 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Matrix22.h"

#include "Determinant.h"
#include "Matrix22d.h"
#include "Vector2.h"

#include <cassert>
#include <utility>

Matrix22::Matrix22(float const * pM)
{
    memcpy(m_M, pM, sizeof(m_M));
}

Matrix22::Matrix22(Vector2 const & x, Vector2 const & y)
    : m_Xx(x.m_X)
    , m_Xy(x.m_Y)
    , m_Yx(y.m_X)
    , m_Yy(y.m_Y)
{
}

Matrix22::Matrix22(Matrix22d const & m22d)
    : m_Xx(float(m22d.m_Xx))
    , m_Xy(float(m22d.m_Xy))
    , m_Yx(float(m22d.m_Yx))
    , m_Yy(float(m22d.m_Yy))
{
}

double Matrix22::Determinant() const
{
    return Determinant2(*this);
}

Matrix22 & Matrix22::Transpose()
{
    std::swap(m_Xy, m_Yx);

    return *this;
}

Matrix22 & Matrix22::Invert()
{
    Matrix22 const a(*this);
    float const    det = float(a.Determinant());

    assert(!MyMath::IsCloseToZero(det));

    if (!MyMath::IsCloseToZero(det))
    {
        m_Xx =  a.m_Yy / det;
        m_Xy = -a.m_Xy / det;

        m_Yx = -a.m_Yx / det;
        m_Yy =  a.m_Xx / det;
    }
    else
    {
        *this = Matrix22::Identity();
    }

    return *this;
}

Matrix22 & Matrix22::PostConcatenate(Matrix22 const & b)
{
    Matrix22 c;

    c.m_Xx = m_Xx * b.m_Xx + m_Xy * b.m_Yx;
    c.m_Yx = m_Yx * b.m_Xx + m_Yy * b.m_Yx;
    c.m_Xy = m_Xx * b.m_Xy + m_Xy * b.m_Yy;
    c.m_Yy = m_Yx * b.m_Xy + m_Yy * b.m_Yy;

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}

Matrix22 & Matrix22::PreConcatenate(Matrix22 const & b)
{
    Matrix22 c;

    c.m_Xx = b.m_Xx * m_Xx + b.m_Xy * m_Yx;
    c.m_Yx = b.m_Yx * m_Xx + b.m_Yy * m_Yx;
    c.m_Xy = b.m_Xx * m_Xy + b.m_Xy * m_Yy;
    c.m_Yy = b.m_Yx * m_Xy + b.m_Yy * m_Yy;

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}
