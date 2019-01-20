#include "PrecompiledHeaders.h"

#include "Matrix44d.h"

#include "Determinant.h"
#include "Matrix33d.h"
#include "Matrix43d.h"
#include "Matrix44.h"
#include "Vector3d.h"
#include "Vector4d.h"

#include <utility>

Matrix44d::Matrix44d(double const * pM)
{
    memcpy(m_M, pM, sizeof(m_M));
}

//!
//! @param	m33	Orientation/scale
//! @param	t	Translation

Matrix44d::Matrix44d(Matrix33d const & m33, Vector3d const & t /* = Vector3d::Origin()*/)
    : m_Xx(m33.m_Xx)
    , m_Xy(m33.m_Xy)
    , m_Xz(m33.m_Xz)
    , m_Xw(0.0)
    , m_Yx(m33.m_Yx)
    , m_Yy(m33.m_Yy)
    , m_Yz(m33.m_Yz)
    , m_Yw(0.0)
    , m_Zx(m33.m_Zx)
    , m_Zy(m33.m_Zy)
    , m_Zz(m33.m_Zz)
    , m_Zw(0.0)
    , m_Tx(t.m_X)
    ,    m_Ty(t.m_Y)
    ,    m_Tz(t.m_Z)
    ,    m_Tw(1.0)
{
}

Matrix44d::Matrix44d(Matrix43d const & m43)
    : m_Xx(m43.m_Xx)
    , m_Xy(m43.m_Xy)
    , m_Xz(m43.m_Xz)
    , m_Xw(0.0)
    , m_Yx(m43.m_Yx)
    , m_Yy(m43.m_Yy)
    , m_Yz(m43.m_Yz)
    , m_Yw(0.0)
    , m_Zx(m43.m_Zx)
    , m_Zy(m43.m_Zy)
    , m_Zz(m43.m_Zz)
    , m_Zw(0.0)
    , m_Tx(m43.m_Tx)
    , m_Ty(m43.m_Ty)
    , m_Tz(m43.m_Tz)
    , m_Tw(1.0)
{
}

Matrix44d::Matrix44d(Matrix44 const & m44f)
    : m_Xx(m44f.m_Xx)
    , m_Xy(m44f.m_Xy)
    , m_Xz(m44f.m_Xz)
    , m_Xw(m44f.m_Xw)
    , m_Yx(m44f.m_Yx)
    , m_Yy(m44f.m_Yy)
    , m_Yz(m44f.m_Yz)
    , m_Yw(m44f.m_Yw)
    , m_Zx(m44f.m_Zx)
    , m_Zy(m44f.m_Zy)
    , m_Zz(m44f.m_Zz)
    , m_Zw(m44f.m_Zw)
    , m_Tx(m44f.m_Tx)
    , m_Ty(m44f.m_Ty)
    , m_Tz(m44f.m_Tz)
    , m_Tw(m44f.m_Tw)
{
}

double Matrix44d::Determinant() const
{
    return Determinant4(*this, 0, 1, 2, 3, 0, 1, 2, 3);
}

Matrix44d & Matrix44d::Transpose()
{
    std::swap(m_Xy, m_Yx);
    std::swap(m_Xz, m_Zx);
    std::swap(m_Xw, m_Tx);
    std::swap(m_Yz, m_Zy);
    std::swap(m_Yw, m_Ty);
    std::swap(m_Zw, m_Tz);

    return *this;
}

Matrix44d & Matrix44d::Invert()
{
    double const det = Determinant();

    if (!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE))
    {
        Matrix44d const a(*this);

        m_Xx =  Determinant3(a, 1, 2, 3, 1, 2, 3) / det;
        m_Xy = -Determinant3(a, 0, 2, 3, 1, 2, 3) / det;
        m_Xz =  Determinant3(a, 0, 1, 3, 1, 2, 3) / det;
        m_Xw = -Determinant3(a, 0, 1, 2, 1, 2, 3) / det;

        m_Yx = -Determinant3(a, 1, 2, 3, 0, 2, 3) / det;
        m_Yy =  Determinant3(a, 0, 2, 3, 0, 2, 3) / det;
        m_Yz = -Determinant3(a, 0, 1, 3, 0, 2, 3) / det;
        m_Yw =  Determinant3(a, 0, 1, 2, 0, 2, 3) / det;

        m_Zx =  Determinant3(a, 1, 2, 3, 0, 1, 3) / det;
        m_Zy = -Determinant3(a, 0, 2, 3, 0, 1, 3) / det;
        m_Zz =  Determinant3(a, 0, 1, 3, 0, 1, 3) / det;
        m_Zw = -Determinant3(a, 0, 1, 2, 0, 1, 3) / det;

        m_Tx = -Determinant3(a, 1, 2, 3, 0, 1, 2) / det;
        m_Ty =  Determinant3(a, 0, 2, 3, 0, 1, 2) / det;
        m_Tz = -Determinant3(a, 0, 1, 3, 0, 1, 2) / det;
        m_Tw =  Determinant3(a, 0, 1, 2, 0, 1, 2) / det;
    }
    else
    {
        *this = Matrix44d::Identity();
    }

    return *this;
}

Matrix44d & Matrix44d::PostConcatenate(Matrix44d const & b)
{
    Matrix44d c;

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

Matrix44d & Matrix44d::PreConcatenate(Matrix44d const & b)
{
    Matrix44d c;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.m_M[i][j] =   b.m_M[i][0] * m_M[0][j]
                          + b.m_M[i][1] * m_M[1][j]
                          + b.m_M[i][2] * m_M[2][j]
                          + b.m_M[i][3] * m_M[3][j];
        }
    }

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}
