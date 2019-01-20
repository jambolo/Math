#include "PrecompiledHeaders.h"

#include "Matrix33d.h"

#include "Determinant.h"
#include "Matrix33.h"
#include "Matrix43d.h"
#include "Matrix44d.h"
#include "Vector3d.h"

#include <cstring>
#include <utility>

Matrix33d::Matrix33d(double const * pM)
{
    memcpy(m_M, pM, sizeof(m_M));
}

Matrix33d::Matrix33d(Vector3d const & x, Vector3d const & y, Vector3d const & z)
    : m_Xx(x.m_X)
    , m_Xy(x.m_Y)
    , m_Xz(x.m_Z)
    , m_Yx(y.m_X)
    , m_Yy(y.m_Y)
    , m_Yz(y.m_Z)
    , m_Zx(z.m_X)
    , m_Zy(z.m_Y)
    , m_Zz(z.m_Z)
{
}

Matrix33d::Matrix33d(Matrix33 const & m33)
    : m_Xx(m33.m_Xx)
    , m_Xy(m33.m_Xy)
    , m_Xz(m33.m_Xz)
    , m_Yx(m33.m_Yx)
    , m_Yy(m33.m_Yy)
    , m_Yz(m33.m_Yz)
    , m_Zx(m33.m_Zx)
    , m_Zy(m33.m_Zy)
    , m_Zz(m33.m_Zz)
{
}

//!
//! This function constructs a 3x3 matrix by extracting it from the 4x3 matrix.

Matrix33d::Matrix33d(Matrix43d const & m43)
{
    memcpy(&m_M[0][0], &m43.m_M[0][0], sizeof(m_M));
}

//!
//! This function constructs a 3x3 matrix by extracting it from the 4x4 matrix.

Matrix33d::Matrix33d(Matrix44d const & m44)
    : m_Xx(m44.m_Xx)
    , m_Xy(m44.m_Xy)
    , m_Xz(m44.m_Xz)
    , m_Yx(m44.m_Yx)
    , m_Yy(m44.m_Yy)
    , m_Yz(m44.m_Yz)
    , m_Zx(m44.m_Zx)
    , m_Zy(m44.m_Zy)
    , m_Zz(m44.m_Zz)
{
}

double Matrix33d::Determinant() const
{
    return Determinant3(*this);
}

Matrix33d & Matrix33d::Transpose()
{
    std::swap(m_Xy, m_Yx);
    std::swap(m_Xz, m_Zx);
    std::swap(m_Yz, m_Zy);

    return *this;
}

Matrix33d & Matrix33d::Invert()
{
    double const det = Determinant();

    assert(!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(det, MyMath::DEFAULT_DOUBLE_TOLERANCE))
    {
        Matrix33d const a(*this);

        m_Xx =  Determinant2(a, 1, 2, 1, 2) / det;
        m_Xy = -Determinant2(a, 0, 2, 1, 2) / det;
        m_Xz =  Determinant2(a, 0, 1, 1, 2) / det;

        m_Yx = -Determinant2(a, 1, 2, 0, 2) / det;
        m_Yy =  Determinant2(a, 0, 2, 0, 2) / det;
        m_Yz = -Determinant2(a, 0, 1, 0, 2) / det;

        m_Zx =  Determinant2(a, 1, 2, 0, 1) / det;
        m_Zy = -Determinant2(a, 0, 2, 0, 1) / det;
        m_Zz =  Determinant2(a, 0, 1, 0, 1) / det;
    }
    else
    {
        *this = Matrix33d::Identity();
    }

    return *this;
}

Matrix33d & Matrix33d::PostConcatenate(Matrix33d const & b)
{
    Matrix33d c;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c.m_M[i][j] =   m_M[i][0] * b.m_M[0][j]
                          + m_M[i][1] * b.m_M[1][j]
                          + m_M[i][2] * b.m_M[2][j];
        }
    }

    return *this;
}

Matrix33d & Matrix33d::PreConcatenate(Matrix33d const & b)
{
    Matrix33d c;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c.m_M[i][j] =   b.m_M[i][0] * m_M[0][j]
                          + b.m_M[i][1] * m_M[1][j]
                          + b.m_M[i][2] * m_M[2][j];
        }
    }

    return *this;
}
