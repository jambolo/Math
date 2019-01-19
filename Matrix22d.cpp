/** @file *//********************************************************************************************************

                                                     Matrix22d.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Matrix22d.cpp#8 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Matrix22d.h"

#include "Determinant.h"
#include "Matrix22.h"
#include "Vector2d.h"

#include <cassert>
#include <utility>

Matrix22d::Matrix22d(double const * pM)
{
    memcpy(m_M, pM, sizeof(m_M));
}

Matrix22d::Matrix22d(Vector2d const & x, Vector2d const & y)
    : m_Xx(x.m_X)
    , m_Xy(x.m_Y)
    , m_Yx(y.m_X)
    , m_Yy(y.m_Y)
{
}

Matrix22d::Matrix22d(Matrix22 const & m22)
    : m_Xx(m22.m_Xx)
    , m_Xy(m22.m_Xy)
    , m_Yx(m22.m_Yx)
    , m_Yy(m22.m_Yy)
{
}

double Matrix22d::Determinant() const
{
    return Determinant2(*this);
}

Matrix22d & Matrix22d::Transpose()
{
    std::swap(m_Xy, m_Yx);

    return *this;
}

Matrix22d & Matrix22d::Invert()
{
    double const det = Determinant();

    assert(!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE))
    {
        Matrix22d const a(*this);

        m_Xx =  a.m_Yy / det;
        m_Xy = -a.m_Xy / det;

        m_Yx = -a.m_Yx / det;
        m_Yy =  a.m_Xx / det;
    }
    else
    {
        *this = Matrix22d::Identity();
    }

    return *this;
}

Matrix22d & Matrix22d::PostConcatenate(Matrix22d const & b)
{
    Matrix22d c;

    c.m_Xx = m_Xx * b.m_Xx + m_Xy * b.m_Yx;
    c.m_Yx = m_Yx * b.m_Xx + m_Yy * b.m_Yx;
    c.m_Xy = m_Xx * b.m_Xy + m_Xy * b.m_Yy;
    c.m_Yy = m_Yx * b.m_Xy + m_Yy * b.m_Yy;

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}

Matrix22d & Matrix22d::PreConcatenate(Matrix22d const & b)
{
    Matrix22d c;

    c.m_Xx = b.m_Xx * m_Xx + b.m_Xy * m_Yx;
    c.m_Yx = b.m_Yx * m_Xx + b.m_Yy * m_Yx;
    c.m_Xy = b.m_Xx * m_Xy + b.m_Xy * m_Yy;
    c.m_Yy = b.m_Yx * m_Xy + b.m_Yy * m_Yy;

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}
