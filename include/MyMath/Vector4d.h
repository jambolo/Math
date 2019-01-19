/** @file *//********************************************************************************************************

                                                      Vector4d.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Vector4d.h#9 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

class Matrix43d;
class Matrix44d;
class Quaternion;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 4D vector of doubles.
//
//! @ingroup Vectors
//!

class Vector4d
{
public:

    //! Constructor
    Vector4d() {}

    //! Constructor
    Vector4d(double x, double y, double z, double w);

    //! Constructor
    Vector4d(double const v[4]);

    //! Returns the length of the vector squared.
    double Length2()                           const;

    //! Returns the length of the vector.
    double Length()                            const;

    //! Returns the inverse of the length of the vector (or 1 if the length is 0)
    double ILength()                           const;

    //! Returns the inverse of the length squared of the vector (or 1 if the length is 0)
    double ILength2()                          const;

    //! Returns true if the vector is normalized (within a tolerance).
    bool IsNormalized()                      const;

    //! Negates the vector. Returns the result.
    Vector4d const & Negate();

    //! Normalizes the vector. Returns the result.
    Vector4d const & Normalize();

    //! Adds a vector. Returns the result.
    Vector4d const & Add(Vector4d const & b);

    //! Subtracts a vector. Returns the result.
    Vector4d const & Subtract(Vector4d const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector4d const & Scale(double scale);

    //! Transforms the vector (vM). Returns the result.
    Vector4d const & Transform(Matrix43d const & m);

    //! Transforms the vector (vM). Returns the result.
    Vector4d const & Transform(Matrix44d const & m);

    //! Rotates the vector around an axis. Returns the result.
    Vector4d const & Rotate(Vector4d const & axis, double angle);

    //! Rotates the vector. Returns the result.
    Vector4d const & Rotate(Quaternion const & q);

    //! Adds a vector. Returns the result.
    Vector4d const & operator +=(Vector4d const & b);

    //! Subtracts a vector. Returns the result.
    Vector4d const & operator -=(Vector4d const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector4d const & operator *=(double scale);

    //! Transforms the vector. Returns the result.
    Vector4d const & operator *=(Matrix43d const & m);

    //! Transforms the vector. Returns the result.
    Vector4d const & operator *=(Matrix44d const & m);

    //! Returns the negative.
    Vector4d operator -()                        const;

    union
    {
        double m_V[4];      //!< Elements as an array {x, y, z, w}
        struct
        {
            double /** */ m_X, m_Y, m_Z, m_W;
        };
    };

    // Useful constants

    //! Returns [0, 0, 0, 0].
    static Vector4d Origin();

    //! Returns [1, 0, 0, 0].
    static Vector4d XAxis();

    //! Returns [0, 1, 0, 0].
    static Vector4d YAxis();

    //! Returns [0, 0, 1, 0].
    static Vector4d ZAxis();

    //! Returns [0, 0, 0, 1].
    static Vector4d WAxis();
};

#pragma warning( pop )

//! @name Vector4d Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector4d operator +(Vector4d const & a, Vector4d const & b);

//! Returns the difference between @a a and @a b.
Vector4d operator -(Vector4d const & a, Vector4d const & b);

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *(Vector4d const & v, Matrix43d const & m);

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *(Matrix43d const & m, Vector4d const & v);

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *(Vector4d const & v, Matrix44d const & m);

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *(Matrix44d const & m, Vector4d const & v);

//! Returns the dot product of a and b.
double Dot(Vector4d const & a, Vector4d const & b);

//! Returns the result of scaling v by s.
Vector4d operator *(Vector4d const & v, double s);

//! Returns the result of scaling v by s.
Vector4d operator *(double s, Vector4d const & v);

//@}

// Inline functions

#include "MyMath.h"

#include <cassert>
#include <cmath>

inline Vector4d::Vector4d(double x, double y, double z, double w)
    : m_X(x)
    , m_Y(y)
    , m_Z(z)
    , m_W(w)
{
}

inline Vector4d::Vector4d(double const v[4])
    : m_X(v[0])
    , m_Y(v[1])
    , m_Z(v[2])
    , m_W(v[3])
{
}

inline double Vector4d::Length2() const
{
    return m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W;
}

inline double Vector4d::Length() const
{
    return sqrt(Length2());
}

inline double Vector4d::ILength() const
{
    double const len = Length();

    assert(!MyMath::IsCloseToZero(len, MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(len, MyMath::DEFAULT_DOUBLE_TOLERANCE))
        return 1.0 / len;
    else
        return 1.0;
}

inline double Vector4d::ILength2() const
{
    double const len2 = Length2();

    assert(!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_DOUBLE_TOLERANCE));

    if (!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_DOUBLE_TOLERANCE))
        return 1.0 / len2;
    else
        return 1.0;
}

inline bool Vector4d::IsNormalized() const
{
    return MyMath::IsCloseTo(Length2(), 1.0, 2.0 * MyMath::DEFAULT_DOUBLE_NORMALIZED_TOLERANCE);
}

inline Vector4d const & Vector4d::Negate()
{
    m_X = -m_X;
    m_Y = -m_Y;
    m_Z = -m_Z;
    m_W = -m_W;

    return *this;
}

inline Vector4d const & Vector4d::Normalize()
{
    return Scale(ILength());
}

inline Vector4d const & Vector4d::Add(Vector4d const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;
    m_Z += b.m_Z;
    m_W += b.m_W;

    return *this;
}

inline Vector4d const & Vector4d::Subtract(Vector4d const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;
    m_Z -= b.m_Z;
    m_W -= b.m_W;

    return *this;
}

inline Vector4d const & Vector4d::Scale(double scale)
{
    m_X *= scale;
    m_Y *= scale;
    m_Z *= scale;
    m_W *= scale;

    return *this;
}

inline Vector4d const & Vector4d::operator +=(Vector4d const & b)
{
    return Add(b);
}

inline Vector4d const & Vector4d::operator -=(Vector4d const & b)
{
    return Subtract(b);
}

inline Vector4d const & Vector4d::operator *=(double scale)
{
    return Scale(scale);
}

//!
//! @note	In order to multiply, a 4th row/column with a value of [0, 0, 0, 1] is implicit.

inline Vector4d const & Vector4d::operator *=(Matrix43d const & m)
{
    return Transform(m);
}

inline Vector4d const & Vector4d::operator *=(Matrix44d const & m)
{
    return Transform(m);
}

inline Vector4d Vector4d::operator -() const
{
    return Vector4d(*this).Negate();
}

inline Vector4d Vector4d::Origin()
{
    return Vector4d(0.0, 0.0, 0.0, 0.0);
}

inline Vector4d Vector4d::XAxis()
{
    return Vector4d(1.0, 0.0, 0.0, 0.0);
}

inline Vector4d Vector4d::YAxis()
{
    return Vector4d(0.0, 1.0, 0.0, 0.0);
}

inline Vector4d Vector4d::ZAxis()
{
    return Vector4d(0.0, 0.0, 1.0, 0.0);
}

inline Vector4d Vector4d::WAxis()
{
    return Vector4d(0.0, 0.0, 0.0, 1.0);
}

inline Vector4d operator +(Vector4d const & a, Vector4d const & b)
{
    return Vector4d(a).Add(b);
}

inline Vector4d operator -(Vector4d const & a, Vector4d const & b)
{
    return Vector4d(a).Subtract(b);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th column with a value of [0, 0, 0, 1] is implicit.

inline Vector4d operator *(Vector4d const & v, Matrix43d const & m)
{
    return Vector4d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th column with a value of [0, 0, 0, 1] is implicit.

inline Vector4d operator *(Matrix43d const & m, Vector4d const & v)
{
    return Vector4d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4d operator *(Vector4d const & v, Matrix44d const & m)
{
    return Vector4d(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4d operator *(Matrix44d const & m, Vector4d const & v)
{
    return Vector4d(v).Transform(m);
}

inline double Dot(Vector4d const & a, Vector4d const & b)
{
    return a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z + a.m_W * b.m_W;
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4d operator *(Vector4d const & v, double s)
{
    return Vector4d(v).Scale(s);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4d operator *(double s, Vector4d const & v)
{
    return Vector4d(v).Scale(s);
}
