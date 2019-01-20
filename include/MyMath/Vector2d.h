#pragma once

#if !defined(MYMATH_VECTOR2D_H)
#define MYMATH_VECTOR2D_H

class Matrix22d;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 2D vector of doubles.
//
//! @ingroup Vectors
//!

class Vector2d
{
public:

    //! Constructor
    Vector2d() = default;

    //! Constructor
    Vector2d(double x, double y);

    //! Constructor
    Vector2d(double const v[2]);

    //! Returns the length of the vector squared.
    double Length2() const;

    //! Returns the length of the vector.
    double Length() const;

    //! Returns the inverse of the length of the vector (or 1 if the length is 0)
    double ILength() const;

    //! Returns the inverse of the length squared of the vector (or 1 if the length is 0)
    double ILength2() const;

    //! Returns true if the vector is normalized (within a tolerance).
    bool IsNormalized() const;

    //! Negates the vector. Returns the result.
    Vector2d const & Negate();

    //! Normalizes the vector. Returns the result.
    Vector2d const & Normalize();

    //! Adds a vector. Returns the result.
    Vector2d const & Add(Vector2d const & b);

    //! Subtracts a vector. Returns the result.
    Vector2d const & Subtract(Vector2d const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector2d const & Scale(double scale);

    //! Transforms the vector (vM). Returns the result.
    Vector2d const & Transform(Matrix22d const & m);

    //! Rotates the vector around an axis. Returns the result.
    Vector2d const & Rotate(double angle);

    //! Adds a vector. Returns the result.
    Vector2d const & operator +=(Vector2d const & b);

    //! Subtracts a vector. Returns the result.
    Vector2d const & operator -=(Vector2d const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector2d const & operator *=(double scale);

    //! Transforms the vector (vM). Returns the result.
    Vector2d const & operator *=(Matrix22d const & m);

    //! Returns the negative.
    Vector2d operator -() const;

    union
    {
        double m_V[2];      //!< Elements as an array {x, y}
        struct
        {
            double /** */ m_X, m_Y;
        };
    };

    // Useful constants

    //! Returns [0, 0].
    static Vector2d Origin();

    //! Returns [1, 0].
    static Vector2d XAxis();

    //! Returns [0, 1].
    static Vector2d YAxis();
};

#pragma warning( pop )

//! @name Vector2d Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector2d operator +(Vector2d const & a, Vector2d const & b);

//! Returns the difference between @a a and @a b.
Vector2d operator -(Vector2d const & a, Vector2d const & b);

//! Returns the result of transforming @a v by @a m.
Vector2d operator *(Vector2d const & v, Matrix22d const & m);

//! Returns the result of transforming @a v by @a m.
Vector2d operator *(Matrix22d const & m, Vector2d const & v);

//! Returns the dot product of @a a and @a b.
double Dot(Vector2d const & a, Vector2d const & b);

//! Returns the result of scaling @a v by @a s.
Vector2d operator *(Vector2d const & v, double s);

//! Returns the result of scaling @a v by @a s.
Vector2d operator *(double s, Vector2d const & v);

//@}

// Inline functions

#include "MyMath.h"

#include <cassert>
#include <cmath>

inline Vector2d::Vector2d(double x, double y)
    : m_X(x)
    , m_Y(y)
{
}

inline Vector2d::Vector2d(double const v[2])
    : m_X(v[0])
    , m_Y(v[1])
{
}

inline double Vector2d::Length2() const
{
    return m_X * m_X + m_Y * m_Y;
}

inline double Vector2d::Length() const
{
    return sqrt(Length2());
}

inline double Vector2d::ILength() const
{
    double const len = Length();

    assert(!MyMath::IsCloseToZero(len, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(len, MyMath::DEFAULT_DOUBLE_TOLERANCE))
        return 1.0 / len;
    else
        return 1.0;
}

inline double Vector2d::ILength2() const
{
    double const len2 = Length2();

    assert(!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_DOUBLE_TOLERANCE))
        return 1.0 / len2;
    else
        return 1.0;
}

inline bool Vector2d::IsNormalized() const
{
    return MyMath::IsCloseTo(Length2(), 1.0, 2.0 * MyMath::DEFAULT_DOUBLE_NORMALIZED_TOLERANCE);
}

inline Vector2d const & Vector2d::Negate()
{
    m_X = -m_X;
    m_Y = -m_Y;

    return *this;
}

inline Vector2d const & Vector2d::Normalize()
{
    return Scale(ILength());
}

inline Vector2d const & Vector2d::Add(Vector2d const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;

    return *this;
}

inline Vector2d const & Vector2d::Subtract(Vector2d const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;

    return *this;
}

inline Vector2d const & Vector2d::Scale(double scale)
{
    m_X *= scale;
    m_Y *= scale;

    return *this;
}

inline Vector2d const & Vector2d::operator +=(Vector2d const & b)
{
    return Add(b);
}

inline Vector2d const & Vector2d::operator -=(Vector2d const & b)
{
    return Subtract(b);
}

inline Vector2d const & Vector2d::operator *=(double scale)
{
    return Scale(scale);
}

inline Vector2d const & Vector2d::operator *=(Matrix22d const & m)
{
    return Transform(m);
}

inline Vector2d Vector2d::operator -() const
{
    return Vector2d(*this).Negate();
}

inline Vector2d Vector2d::Origin()
{
    return Vector2d(0.0, 0.0);
}

inline Vector2d Vector2d::XAxis()
{
    return Vector2d(1.0, 0.0);
}

inline Vector2d Vector2d::YAxis()
{
    return Vector2d(0.0, 1.0);
}

inline Vector2d operator +(Vector2d const & a, Vector2d const & b)
{
    return Vector2d(a).Add(b);
}

inline Vector2d operator -(Vector2d const & a, Vector2d const & b)
{
    return Vector2d(a).Subtract(b);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2d operator *(Vector2d const & v, Matrix22d const & m)
{
    return Vector2d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2d operator *(Matrix22d const & m, Vector2d const & v)
{
    return Vector2d(v).Transform(m);
}

inline double Dot(Vector2d const & a, Vector2d const & b)
{
    return a.m_X * b.m_X + a.m_Y * b.m_Y;
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2d operator *(Vector2d const & v, double s)
{
    return Vector2d(v).Scale(s);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2d operator *(double s, Vector2d const & v)
{
    return Vector2d(v).Scale(s);
}

#endif // !defined(MYMATH_VECTOR2D_H)
