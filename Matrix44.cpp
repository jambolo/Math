/** @file *//********************************************************************************************************

                                                    Matrix44.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Matrix44.cpp#13 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Matrix44.h"

#include "Determinant.h"
#include "Matrix33.h"
#include "Matrix43.h"
#include "Matrix44d.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cassert>
#include <utility>

Matrix44::Matrix44(float const * pM)
{
    memcpy(m_M, pM, sizeof(m_M));
}

//!
//! @param m33	Orientation/scale
//! @param t	Translation

Matrix44::Matrix44(Matrix33 const & m33, Vector3 const & t /* = Vector3::Origin()*/)
    : m_Xx(m33.m_Xx)
    , m_Xy(m33.m_Xy)
    , m_Xz(m33.m_Xz)
    , m_Xw(0.0f)
    , m_Yx(m33.m_Yx)
    , m_Yy(m33.m_Yy)
    , m_Yz(m33.m_Yz)
    , m_Yw(0.0f)
    , m_Zx(m33.m_Zx)
    , m_Zy(m33.m_Zy)
    , m_Zz(m33.m_Zz)
    , m_Zw(0.0f)
    , m_Tx(t.m_X)
    ,    m_Ty(t.m_Y)
    ,    m_Tz(t.m_Z)
    ,    m_Tw(1.0f)
{
}

Matrix44::Matrix44(Matrix43 const & m43)
    : m_Xx(m43.m_Xx)
    , m_Xy(m43.m_Xy)
    , m_Xz(m43.m_Xz)
    , m_Xw(0.0f)
    , m_Yx(m43.m_Yx)
    , m_Yy(m43.m_Yy)
    , m_Yz(m43.m_Yz)
    , m_Yw(0.0f)
    , m_Zx(m43.m_Zx)
    , m_Zy(m43.m_Zy)
    , m_Zz(m43.m_Zz)
    , m_Zw(0.0f)
    , m_Tx(m43.m_Tx)
    , m_Ty(m43.m_Ty)
    , m_Tz(m43.m_Tz)
    , m_Tw(1.0f)
{
}

Matrix44::Matrix44(Matrix44d const & m44d)
    : m_Xx(float(m44d.m_Xx))
    , m_Xy(float(m44d.m_Xy))
    , m_Xz(float(m44d.m_Xz))
    , m_Xw(float(m44d.m_Xw))
    , m_Yx(float(m44d.m_Yx))
    , m_Yy(float(m44d.m_Yy))
    , m_Yz(float(m44d.m_Yz))
    , m_Yw(float(m44d.m_Yw))
    , m_Zx(float(m44d.m_Zx))
    , m_Zy(float(m44d.m_Zy))
    , m_Zz(float(m44d.m_Zz))
    , m_Zw(float(m44d.m_Zw))
    , m_Tx(float(m44d.m_Tx))
    , m_Ty(float(m44d.m_Ty))
    , m_Tz(float(m44d.m_Tz))
    , m_Tw(float(m44d.m_Tw))
{
}

double Matrix44::Determinant() const
{
    return Determinant4(*this);
}

Matrix44 & Matrix44::Transpose()
{
    std::swap(m_Xy, m_Yx);
    std::swap(m_Xz, m_Zx);
    std::swap(m_Xw, m_Tx);
    std::swap(m_Yz, m_Zy);
    std::swap(m_Yw, m_Ty);
    std::swap(m_Zw, m_Tz);

    return *this;
}

Matrix44 & Matrix44::Invert()
{
    Matrix44 const a(*this);
    double const   det = a.Determinant();

    assert(!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE))
    {
        m_Xx = float(Determinant3(a, 1, 2, 3, 1, 2, 3) / det);
        m_Xy = float(-Determinant3(a, 0, 2, 3, 1, 2, 3) / det);
        m_Xz = float(Determinant3(a, 0, 1, 3, 1, 2, 3) / det);
        m_Xw = float(-Determinant3(a, 0, 1, 2, 1, 2, 3) / det);

        m_Yx = float(-Determinant3(a, 1, 2, 3, 0, 2, 3) / det);
        m_Yy = float(Determinant3(a, 0, 2, 3, 0, 2, 3) / det);
        m_Yz = float(-Determinant3(a, 0, 1, 3, 0, 2, 3) / det);
        m_Yw = float(Determinant3(a, 0, 1, 2, 0, 2, 3) / det);

        m_Zx = float(Determinant3(a, 1, 2, 3, 0, 1, 3) / det);
        m_Zy = float(-Determinant3(a, 0, 2, 3, 0, 1, 3) / det);
        m_Zz = float(Determinant3(a, 0, 1, 3, 0, 1, 3) / det);
        m_Zw = float(-Determinant3(a, 0, 1, 2, 0, 1, 3) / det);

        m_Tx = float(-Determinant3(a, 1, 2, 3, 0, 1, 2) / det);
        m_Ty = float(Determinant3(a, 0, 2, 3, 0, 1, 2) / det);
        m_Tz = float(-Determinant3(a, 0, 1, 3, 0, 1, 2) / det);
        m_Tw = float(Determinant3(a, 0, 1, 2, 0, 1, 2) / det);
    }
    else
    {
        *this = Matrix44::Identity();
    }

    return *this;
}

Matrix44 & Matrix44::PostConcatenate(Matrix44 const & b)
{
    Matrix44 c;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.m_M[i][j] =   m_M[i][0] * b.m_M[0][j]
                          + m_M[i][1] * b.m_M[1][j]
                          + m_M[i][2] * b.m_M[2][j]
                          + m_M[i][3] * b.m_M[3][j];
        }
    }

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}

Matrix44 & Matrix44::PreConcatenate(Matrix44 const & b)
{
    Matrix44 c;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.m_M[i][j] =     b.m_M[i][0] * m_M[0][j]
                          + b.m_M[i][1] * m_M[1][j]
                          + b.m_M[i][2] * m_M[2][j]
                          + b.m_M[i][3] * m_M[3][j];
        }
    }

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}
