#include "Matrix43d.h"

#include "Determinant.h"
#include "Matrix33d.h"
#include "Matrix43.h"
#include "Matrix44d.h"
#include "Vector3d.h"

#include <cassert>

Matrix43d::Matrix43d(double const * pM)
{
    memcpy(m_M, pM, sizeof(m_M));
}

//!
//! @param	m33	Orientation/scale
//! @param	t	Translation

Matrix43d::Matrix43d(Matrix33d const & m33,
                     Vector3d const &  t /* = Vector3d::Origin()*/)
    : m_Xx(m33.m_Xx)
    , m_Xy(m33.m_Xy)
    , m_Xz(m33.m_Xz)
    , m_Yx(m33.m_Yx)
    , m_Yy(m33.m_Yy)
    , m_Yz(m33.m_Yz)
    , m_Zx(m33.m_Zx)
    , m_Zy(m33.m_Zy)
    , m_Zz(m33.m_Zz)
    , m_Tx(t.m_X)
    ,    m_Ty(t.m_Y)
    ,    m_Tz(t.m_Z)
{
}

Matrix43d::Matrix43d(Matrix43 const & m43)
    : m_Xx(m43.m_Xx)
    , m_Xy(m43.m_Xy)
    , m_Xz(m43.m_Xz)
    , m_Yx(m43.m_Yx)
    , m_Yy(m43.m_Yy)
    , m_Yz(m43.m_Yz)
    , m_Zx(m43.m_Zx)
    , m_Zy(m43.m_Zy)
    , m_Zz(m43.m_Zz)
    , m_Tx(m43.m_Tx)
    , m_Ty(m43.m_Ty)
    , m_Tz(m43.m_Tz)
{
}

Matrix43d::Matrix43d(Matrix44d const & m44)
    : m_Xx(m44.m_Xx)
    , m_Xy(m44.m_Xy)
    , m_Xz(m44.m_Xz)
    , m_Yx(m44.m_Yx)
    , m_Yy(m44.m_Yy)
    , m_Yz(m44.m_Yz)
    , m_Zx(m44.m_Zx)
    , m_Zy(m44.m_Zy)
    , m_Zz(m44.m_Zz)
    , m_Tx(m44.m_Tx)
    , m_Ty(m44.m_Ty)
    , m_Tz(m44.m_Tz)
{
}

//! You can't actually compute the determinant of a non-square matrix. Since we are using 4x3 matrices to represent
//! 4x4 matrices with a 4th column of [ 0, 0, 0, 1 ], we will just pretend this is that 4x4 matrix.

double Matrix43d::Determinant() const
{
    // Ok, some cleverness. The determinant is normally computed by expanding
    // by minors and excluding the top row. Actually, any row or column can
    // be excluded, but the sign is negated if an odd row or column is
    // excluded (the first row is 0).
    // So let's expand by minors, excluding column 3:
    //
    //	     | Xx Xy Xz 0 |
    //	det( | Yx Yy Yz 0 | )
    //	     | Zx Zy Zz 0 |
    //	     | Tx Ty Tz 1 |
    //
    //                 | Yx Yy Yz |
    //	= -[  0 * det( | Zx Zy Zz | )
    //                 | Tx Ty Tz |
    //
    //                 | Xx Xy Xz |
    //      - 0 * det( | Zx Zy Zz | )
    //                 | Tx Ty Tz |
    //
    //                 | Yx Yy Yz |
    //      + 0 * det( | Yx Yy Yz | )
    //                 | Tx Ty Tz |
    //
    //                 | Xx Xy Xz |
    //      - 1 * det( | Yx Yy Yz | )
    //                 | Zx Zy Zz |
    //     ]
    //
    //         | Xx Xy Xz |
    //	= det( | Yx Yy Yz | ) COOL!!!
    //         | Zx Zy Zz |

    return Determinant3(*this);
}

//! You can't actually invert a 4x3 matrix and get a 4x3 matrix. Since we are using 4x3 matrices to represent 4x4
//! matrices with a 4th column of [ 0, 0, 0, 1 ], we will just pretend this is that 4x4 matrix.

Matrix43d & Matrix43d::Invert()
{
    // Ok, now for the cleverness...
    //
    // M = ( S * R ) * T, where
    //
    //	         | Xx Xy Xz 0 |	     | 1  0  0  0 |
    //	S * R =  | Yx Yy Yz 0 |	T =  | 0  1  0  0 |
    //	         | Zx Zy Zz 0 |	     | 0  0  1  0 |
    //	         | 0  0  0  1 |	     | Tx Ty Tz 1 |
    //
    // So, ~M = ~T * ~( S * R )
    //
    // ~T is computed by negating m_Tx, m_Ty, and m_Tz
    // ~( S * R ) is computed by inverting the UL 3x3 sub-matrix
    // ~T * ~( S * R ) is computed by augmenting the 3x3 result of ~( S * R )
    // with result of -[ m_Tx m_Ty m_Tz ] * ~( S * R )

    // Compute ~( S * R )

    Matrix43d const a(*this);
    double const    detSR = Determinant3(a, 0, 1, 2, 0, 1, 2);

    assert(!MyMath::IsCloseToZero(detSR, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(detSR, MyMath::DEFAULT_DOUBLE_TOLERANCE))
    {
        m_Xx =  Determinant2(a, 1, 2, 1, 2) / detSR;
        m_Xy = -Determinant2(a, 0, 2, 1, 2) / detSR;
        m_Xz =  Determinant2(a, 0, 1, 1, 2) / detSR;

        m_Yx = -Determinant2(a, 1, 2, 0, 2) / detSR;
        m_Yy =  Determinant2(a, 0, 2, 0, 2) / detSR;
        m_Yz = -Determinant2(a, 0, 1, 0, 2) / detSR;

        m_Zx =  Determinant2(a, 1, 2, 0, 1) / detSR;
        m_Zy = -Determinant2(a, 0, 2, 0, 1) / detSR;
        m_Zz =  Determinant2(a, 0, 1, 0, 1) / detSR;
    }
    else
    {
        *this = Matrix43d::Identity();
    }

    // Augment with -[ m_Tx m_Ty m_Tz ] * ~( S * R )

    m_Tx = -(a.m_Tx * m_Xx + a.m_Ty * m_Yx + a.m_Tz * m_Zx);
    m_Ty = -(a.m_Tx * m_Xy + a.m_Ty * m_Yy + a.m_Tz * m_Zy);
    m_Tz = -(a.m_Tx * m_Xz + a.m_Ty * m_Yz + a.m_Tz * m_Zz);

    return *this;
}

//! You can't actually multiply a 4x3 matrix by a 4x3 matrix. Since we are using 4x3 matrices to represent 4x4
//! matrices with a 4th column of [ 0, 0, 0, 1 ], we will just pretend this is that 4x4 matrix.

Matrix43d & Matrix43d::PostConcatenate(Matrix43d const & b)
{
    // Ok, now for the cleverness...
    //
    // Since 4th column is [ 0, 0, 0, 1 ], we can optimize the math a little
    // bit.

    int       j;
    Matrix43d c;

    for (j = 0; j < 3; j++)
    {
        c.m_M[0][j] =   m_M[0][0] * b.m_M[0][j]
                      + m_M[0][1] * b.m_M[1][j]
                      + m_M[0][2] * b.m_M[2][j];
    }

    for (j = 0; j < 3; j++)
    {
        c.m_M[1][j] =   m_M[1][0] * b.m_M[0][j]
                      + m_M[1][1] * b.m_M[1][j]
                      + m_M[1][2] * b.m_M[2][j];
    }

    for (j = 0; j < 3; j++)
    {
        c.m_M[2][j] =   m_M[2][0] * b.m_M[0][j]
                      + m_M[2][1] * b.m_M[1][j]
                      + m_M[2][2] * b.m_M[2][j];
    }

    for (j = 0; j < 3; j++)
    {
        c.m_M[3][j] =   m_M[3][0] * b.m_M[0][j]
                      + m_M[3][1] * b.m_M[1][j]
                      + m_M[3][2] * b.m_M[2][j]
                      +                 b.m_M[3][j];
    }

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}

//! You can't actually multiply a 4x3 matrix by a 4x3 matrix. Since we are using 4x3 matrices to represent 4x4
//! matrices with a 4th column of [ 0, 0, 0, 1 ], we will just pretend this is that 4x4 matrix.

Matrix43d & Matrix43d::PreConcatenate(Matrix43d const & b)
{
    // Ok, now for the cleverness...
    //
    // Since the 4th column is [ 0, 0, 0, 1 ], we can optimize the math a
    // little bit.

    int       j;
    Matrix43d c;

    for (j = 0; j < 3; j++)
    {
        c.m_M[0][j] =   b.m_M[0][0] * m_M[0][j]
                      + b.m_M[0][1] * m_M[1][j]
                      + b.m_M[0][2] * m_M[2][j];
    }

    for (j = 0; j < 3; j++)
    {
        c.m_M[1][j] =   b.m_M[1][0] * m_M[0][j]
                      + b.m_M[1][1] * m_M[1][j]
                      + b.m_M[1][2] * m_M[2][j];
    }

    for (j = 0; j < 3; j++)
    {
        c.m_M[2][j] =   b.m_M[2][0] * m_M[0][j]
                      + b.m_M[2][1] * m_M[1][j]
                      + b.m_M[2][2] * m_M[2][j];
    }

    for (j = 0; j < 3; j++)
    {
        c.m_M[3][j] =   b.m_M[3][0] * m_M[0][j]
                      + b.m_M[3][1] * m_M[1][j]
                      + b.m_M[3][2] * m_M[2][j]
                      +                   m_M[3][j];
    }

    memcpy(m_M, c.m_M, sizeof(m_M));

    return *this;
}
