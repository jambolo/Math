#pragma once

#if !defined(MYMATH_VECTOR3D_H)
#define MYMATH_VECTOR3D_H

class Matrix33d;
class Matrix43d;
class Quaternion;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 3D vector of doubles.
//!
//! @ingroup Vectors
//!

class Vector3d
{
public:

    //! Constructor.
    Vector3d() = default;

    //! Constructor.
    Vector3d(double x, double y, double z);

    //! Constructor.
    Vector3d(double const v[3]);

    //! Returns the length of the vector squared.
    double Length2() const;

    //! Returns the length of the vector.
    double Length() const;

    //! Returns the inverse of the length of the vector (or 1. if the length is 0)
    double ILength() const;

    //! Returns the inverse of the length squared of the vector (or 1. if the length is 0)
    double ILength2() const;

    //! Returns true if the vector is normalized (within a tolerance).
    bool IsNormalized() const;

    //! Negates the vector. Returns the result.
    Vector3d const & Negate();

    //! Normalizes the vector. Returns the result.
    Vector3d const & Normalize();

    //! Adds a vector. Returns the result.
    Vector3d const & Add(Vector3d const & b);

    //! Subtracts a vector. Returns the result.
    Vector3d const & Subtract(Vector3d const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector3d const & Scale(double scale);

    //! Transforms the vector (vM). Returns the result.
    Vector3d const & Transform(Matrix43d const & m);

    //! Transforms the vector (vM). Returns the result.
    Vector3d const & Transform(Matrix33d const & m);

    //! Rotates the vector around an axis. Returns the result.
    Vector3d const & Rotate(Vector3d const & axis, double angle);

    //! Rotates the vector. Returns the result.
    Vector3d const & Rotate(Quaternion const & q);

    //! Adds a vector. Returns the result.
    Vector3d const & operator +=(Vector3d const & b);

    //! Subtracts a vector. Returns the result.
    Vector3d const & operator -=(Vector3d const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector3d const & operator *=(double scale);

    //! Transforms the vector (vM). Returns the result.
    Vector3d const & operator *=(Matrix43d const & m);

    //! Transforms the vector (vM). Returns the result.
    Vector3d const & operator *=(Matrix33d const & m);

    //! Returns the negative.
    Vector3d operator -() const;

    union
    {
        double m_V[3];      //!< Elements as an array {x, y, z}
        struct
        {
            double /** */ m_X, m_Y, m_Z;
        };
    };

    // Useful constants

    //! Returns [0, 0, 0].
    static Vector3d Origin();

    //! Returns [1, 0, 0].
    static Vector3d XAxis();

    //! Returns [0, 1, 0].
    static Vector3d YAxis();

    //! Returns [0, 0, 1].
    static Vector3d ZAxis();
};

#pragma warning( pop )

//! @name Vector3d Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector3d operator +(Vector3d const & a, Vector3d const & b);

//! Returns the difference between @a a and @a b.
Vector3d operator -(Vector3d const & a, Vector3d const & b);

//! Returns the result of transforming @a v by @a m.
Vector3d operator *(Vector3d const & v, Matrix43d const & m);

//! Returns the result of transforming @a v by @a m.
Vector3d operator *(Matrix43d const & m, Vector3d const & v);

//! Returns the result of transforming @a v by @a m.
Vector3d operator *(Vector3d const & v, Matrix33d const & m);

//! Returns the result of transforming @a v by @a m.
Vector3d operator *(Matrix33d const & m, Vector3d const & v);

//! Returns the dot product of @a a and @a b.
double Dot(Vector3d const & a, Vector3d const & b);

//! Returns the cross product of @a a and @a b.
Vector3d Cross(Vector3d const & a, Vector3d const & b);

//! Returns the result of scaling @a v by @a s.
Vector3d operator *(Vector3d const & v, double s);

//! Returns the result of scaling @a v by @a s.
Vector3d operator *(double s, Vector3d const & v);

//@}

// Inline functions

#include "MyMath.h"

#include <cassert>
#include <cmath>

inline Vector3d::Vector3d(double x, double y, double z)
    : m_X(x)
    , m_Y(y)
    , m_Z(z)
{
}

inline Vector3d::Vector3d(double const v[3])
    : m_X(v[0])
    , m_Y(v[1])
    , m_Z(v[2])
{
}

inline double Vector3d::Length2() const
{
    return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
}

inline double Vector3d::Length() const
{
    return sqrt(Length2());
}

inline double Vector3d::ILength() const
{
    double const len = Length();

    assert(!MyMath::IsCloseToZero(len, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(len, MyMath::DEFAULT_DOUBLE_TOLERANCE))
        return 1.0 / len;
    else
        return 1.0;
}

inline double Vector3d::ILength2() const
{
    double const len2 = Length2();

    assert(!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_DOUBLE_TOLERANCE))
        return 1.0 / len2;
    else
        return 1.0;
}

inline bool Vector3d::IsNormalized() const
{
    return MyMath::IsCloseTo(Length2(), 1., 2. * MyMath::DEFAULT_DOUBLE_NORMALIZED_TOLERANCE);
}

inline Vector3d const & Vector3d::Negate()
{
    m_X = -m_X;
    m_Y = -m_Y;
    m_Z = -m_Z;

    return *this;
}

inline Vector3d const & Vector3d::Normalize()
{
    return Scale(ILength());
}

inline Vector3d const & Vector3d::Add(Vector3d const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;
    m_Z += b.m_Z;

    return *this;
}

inline Vector3d const & Vector3d::Subtract(Vector3d const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;
    m_Z -= b.m_Z;

    return *this;
}

inline Vector3d const & Vector3d::Scale(double scale)
{
    m_X *= scale;
    m_Y *= scale;
    m_Z *= scale;

    return *this;
}

inline Vector3d const & Vector3d::operator +=(Vector3d const & b)
{
    return Add(b);
}

inline Vector3d const & Vector3d::operator -=(Vector3d const & b)
{
    return Subtract(b);
}

inline Vector3d const & Vector3d::operator *=(double scale)
{
    return Scale(scale);
}

inline Vector3d const & Vector3d::operator *=(Matrix33d const & m)
{
    return Transform(m);
}

//!
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

inline Vector3d const & Vector3d::operator *=(Matrix43d const & m)
{
    return Transform(m);
}

inline Vector3d Vector3d::operator -() const
{
    return Vector3d(*this).Negate();
}

inline Vector3d Vector3d::Origin()
{
    return Vector3d(0.0, 0.0, 0.0);
}

inline Vector3d Vector3d::XAxis()
{
    return Vector3d(1.0, 0.0, 0.0);
}

inline Vector3d Vector3d::YAxis()
{
    return Vector3d(0.0, 1.0, 0.0);
}

inline Vector3d Vector3d::ZAxis()
{
    return Vector3d(0.0, 0.0, 1.0);
}

inline Vector3d operator +(Vector3d const & a, Vector3d const & b)
{
    return Vector3d(a).Add(b);
}

inline Vector3d operator -(Vector3d const & a, Vector3d const & b)
{
    return Vector3d(a).Subtract(b);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3d operator *(Vector3d const & v, Matrix33d const & m)
{
    return Vector3d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3d operator *(Matrix33d const & m, Vector3d const & v)
{
    return Vector3d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

inline Vector3d operator *(Vector3d const & v, Matrix43d const & m)
{
    return Vector3d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

inline Vector3d operator *(Matrix43d const & m, Vector3d const & v)
{
    return Vector3d(v).Transform(m);
}

inline double Dot(Vector3d const & a, Vector3d const & b)
{
    return a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z;
}

inline Vector3d Cross(Vector3d const & a, Vector3d const & b)
{
    return Vector3d(a.m_Y * b.m_Z - a.m_Z * b.m_Y,
                    a.m_Z * b.m_X - a.m_X * b.m_Z,
                    a.m_X * b.m_Y - a.m_Y * b.m_X);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3d operator *(Vector3d const & v, double s)
{
    return Vector3d(v).Scale(s);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3d operator *(double s, Vector3d const & v)
{
    return Vector3d(v).Scale(s);
}

#endif // !defined(MYMATH_VECTOR3D_H)
