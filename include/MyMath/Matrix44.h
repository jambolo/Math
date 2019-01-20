#pragma once

#if !defined(MYMATH_MATRIX44_H)
#define MYMATH_MATRIX44_H

#include "Vector3.h"

class Matrix33;
class Matrix43;
class Matrix44d;
class Vector4;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 4x4 matrix of floats.
//
//! @ingroup Matrices
//!

class Matrix44
{
public:

    //! Constructor
    Matrix44() = default;

    //! Constructor
    Matrix44(float Xx, float Xy, float Xz, float Xw,
             float Yx, float Yy, float Yz, float Yw,
             float Zx, float Zy, float Zz, float Zw,
             float Tx, float Ty, float Tz, float Tw);

    //! Constructor
    Matrix44(Vector3 const & x,
             Vector3 const & y,
             Vector3 const & z,
             Vector3 const & t = Vector3::Origin());

    //! Constructor
    explicit Matrix44(float const * pM);

    //! Constructor
    Matrix44(Matrix33 const & m33, Vector3 const & t = Vector3::Origin());

    //! Conversion
    explicit Matrix44(Matrix43 const & m43);

    //! Conversion
    explicit Matrix44(Matrix44d const & m44d);

    //! Returns the X vector.
    Vector4 const & GetX() const;

    //! Returns the Y vector.
    Vector4 const & GetY() const;

    //! Returns the Z vector.
    Vector4 const & GetZ() const;

    //! Returns the T (or W) vector.
    Vector4 const & GetT() const;

    //! Returns the determinant.
    double Determinant() const;

    //! Returns true if the matrix is orthonormal (within a tolerance)
    bool IsOrthonormal() const;

    //! Transposes the matrix. Returns the result.
    Matrix44 & Transpose();

    //! Inverts the matrix. Returns the result.
    Matrix44 & Invert();

    //! Pre-concatenates a matrix. Returns the result.
    Matrix44 & PreConcatenate(Matrix44 const & b);

    //! Post-concatenates a matrix. Returns the result.
    Matrix44 & PostConcatenate(Matrix44 const & b);

    //! Post-concatenates a matrix. Returns the result.
    Matrix44 & operator *=(Matrix44 const & b);

    //! Returns the inverse.
    Matrix44 operator ~() const;

    union
    {
        float m_M[4][4];            //!< Elements as a 4x4 array
        struct
        {
            //! @name	Matrix elements
            //@{
            float /** */ m_Xx, /** */ m_Xy, /** */ m_Xz, /** */ m_Xw;
            float /** */ m_Yx, /** */ m_Yy, /** */ m_Yz, /** */ m_Yw;
            float /** */ m_Zx, /** */ m_Zy, /** */ m_Zz, /** */ m_Zw;
            float /** */ m_Tx, /** */ m_Ty, /** */ m_Tz, /** */ m_Tw;
            //@}
        };
    };

    //! Returns the identity matrix.
    static Matrix44 Identity();
};

#pragma warning( pop )

// Inline functions

#include "Vector3.h"

inline Matrix44::Matrix44(float Xx, float Xy, float Xz, float Xw,
                          float Yx, float Yy, float Yz, float Yw,
                          float Zx, float Zy, float Zz, float Zw,
                          float Tx, float Ty, float Tz, float Tw)

    : m_Xx(Xx)
    , m_Xy(Xy)
    , m_Xz(Xz)
    , m_Xw(Xw)
    , m_Yx(Yx)
    , m_Yy(Yy)
    , m_Yz(Yz)
    , m_Yw(Yw)
    , m_Zx(Zx)
    , m_Zy(Zy)
    , m_Zz(Zz)
    , m_Zw(Zw)
    , m_Tx(Tx)
    , m_Ty(Ty)
    , m_Tz(Tz)
    , m_Tw(Tw)
{
}

inline Matrix44::Matrix44(Vector3 const & x,
                          Vector3 const & y,
                          Vector3 const & z,
                          Vector3 const & t /* = Vector3::Origin()*/)
    : m_Xx(x.m_X)
    , m_Xy(x.m_Y)
    , m_Xz(x.m_Z)
    , m_Xw(0.0f)
    , m_Yx(y.m_X)
    , m_Yy(y.m_Y)
    , m_Yz(y.m_Z)
    , m_Yw(0.0f)
    , m_Zx(z.m_X)
    , m_Zy(z.m_Y)
    , m_Zz(z.m_Z)
    , m_Zw(0.0f)
    , m_Tx(t.m_X)
    , m_Ty(t.m_Y)
    , m_Tz(t.m_Z)
    , m_Tw(1.0f)
{
}

inline Vector4 const & Matrix44::GetX() const
{
    return *reinterpret_cast<Vector4 const *>(&m_Xx);
}

inline Vector4 const & Matrix44::GetY() const
{
    return *reinterpret_cast<Vector4 const *>(&m_Yx);
}

inline Vector4 const & Matrix44::GetZ() const
{
    return *reinterpret_cast<Vector4 const *>(&m_Zx);
}

inline Vector4 const & Matrix44::GetT() const
{
    return *reinterpret_cast<Vector4 const *>(&m_Tx);
}

inline Matrix44 & Matrix44::operator *=(Matrix44 const & b)
{
    return PostConcatenate(b);
}

inline Matrix44 Matrix44::operator ~() const
{
    return Matrix44(*this).Invert();
}

inline Matrix44 Matrix44::Identity()
{
    return Matrix44(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

#endif // !defined(MYMATH_MATRIX44_H)
