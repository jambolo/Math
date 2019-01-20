#pragma once

#if !defined(MYMATH_VECTOR4_H)
#define MYMATH_VECTOR4_H

class Matrix43;
class Matrix44;
class Quaternion;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 4D vector of floats.
//
//! @ingroup Vectors
//!

class Vector4
{
public:

    //! Constructor
    Vector4() = default;

    //! Constructor
    Vector4(float x, float y, float z, float w);

    //! Constructor
    Vector4(float const v[4]);

    //! Returns the length of the vector squared.
    float Length2() const;

    //! Returns the length of the vector.
    float Length() const;

    //! Returns the inverse of the length of the vector (or 1 if the length is 0)
    float ILength() const;

    //! Returns the inverse of the length squared of the vector (or 1 if the length is 0)
    float ILength2() const;

    //! Returns true if the vector is normalized (within a tolerance).
    bool IsNormalized() const;

    //! Negates the vector. Returns the result.
    Vector4 const & Negate();

    //! Normalizes the vector. Returns the result.
    Vector4 const & Normalize();

    //! Adds a vector. Returns the result.
    Vector4 const & Add(Vector4 const & b);

    //! Subtracts a vector. Returns the result.
    Vector4 const & Subtract(Vector4 const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector4 const & Scale(float scale);

    //! Transforms the vector. Returns the result.
    Vector4 const & Transform(Matrix43 const & m);

    //! Transforms the vector. Returns the result
    Vector4 const & Transform(Matrix44 const & m);

    //! Rotates the vector around an axis. Returns the result.
    Vector4 const & Rotate(Vector4 const & axis, float angle);

    //! Rotates the vector
    Vector4 const & Rotate(Quaternion const & q);

    //! Adds a vector. Returns the result.
    Vector4 const & operator +=(Vector4 const & b);

    //! Subtracts a vector. Returns the result.
    Vector4 const & operator -=(Vector4 const & b);

    //! Scales the vector. Returns the result.
    Vector4 const & operator *=(float scale);

    //! Transforms the vector. Returns the result.
    Vector4 const & operator *=(Matrix43 const & m);

    //! Transforms the vector. Returns the result.
    Vector4 const & operator *=(Matrix44 const & m);

    //! Returns the negative.
    Vector4 operator -() const;

    union
    {
        float m_V[4];       //!< Elements as an array {x, y, z, w}
        struct
        {
            float /** */ m_X, m_Y, m_Z, m_W;
        };
    };

    // Useful constants

    //! Returns [0, 0, 0, 0].
    static Vector4 Origin();

    //! Returns [1, 0, 0, 0].
    static Vector4 XAxis();

    //! Returns [0, 1, 0, 0].
    static Vector4 YAxis();

    //! Returns [0, 0, 1, 0].
    static Vector4 ZAxis();

    //! Returns [0, 0, 0, 1].
    static Vector4 WAxis();
};

#pragma warning( pop )

//! @name Vector4 Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector4 operator +(Vector4 const & a, Vector4 const & b);

//! Returns the difference between @a a and @a b.
Vector4 operator -(Vector4 const & a, Vector4 const & b);

//! Returns the result of transforming @a v by @a m.
Vector4 operator *(Vector4 const & v, Matrix43 const & m);

//! Returns the result of transforming @a v by @a m.
Vector4 operator *(Matrix43 const & m, Vector4 const & v);

//! Returns the result of transforming @a v by @a m.
Vector4 operator *(Vector4 const & v, Matrix44 const & m);

//! Returns the result of transforming @a v by @a m.
Vector4 operator *(Matrix44 const & m, Vector4 const & v);

//! Returns the dot product of @a a and @a b.
float Dot(Vector4 const & a, Vector4 const & b);

//! Returns the result of scaling @a v by @a s.
Vector4 operator *(Vector4 const & v, float s);

//! Returns the result of scaling @a v by @a s.
Vector4 operator *(float s, Vector4 const & v);

//@}

// Inline functions

#include "MyMath.h"

#include <cassert>
#include <cmath>

inline Vector4::Vector4(float x, float y, float z, float w)
    : m_X(x)
    , m_Y(y)
    , m_Z(z)
    , m_W(w)
{
}

inline Vector4::Vector4(float const v[4])
    : m_X(v[0])
    , m_Y(v[1])
    , m_Z(v[2])
    , m_W(v[3])
{
}

inline float Vector4::Length2() const
{
    return m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W;
}

inline float Vector4::Length() const
{
    return sqrtf(Length2());
}

inline float Vector4::ILength() const
{
    float const len = Length();

    assert(!MyMath::IsCloseToZero(len, MyMath::DEFAULT_FLOAT_TOLERANCE));

    if (!MyMath::IsCloseToZero(len, MyMath::DEFAULT_FLOAT_TOLERANCE))
        return 1.0f / len;
    else
        return 1.0f;
}

inline float Vector4::ILength2() const
{
    float const len2 = Length2();

    assert(!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_FLOAT_TOLERANCE));

    if (!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_FLOAT_TOLERANCE))
        return 1.0f / len2;
    else
        return 1.0f;
}

inline bool Vector4::IsNormalized() const
{
    return MyMath::IsCloseTo(Length2(), 1.0, 2.0 * MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE);
}

inline Vector4 const & Vector4::Negate()
{
    m_X = -m_X;
    m_Y = -m_Y;
    m_Z = -m_Z;
    m_W = -m_W;

    return *this;
}

inline Vector4 const & Vector4::Normalize()
{
    return Scale(ILength());
}

inline Vector4 const & Vector4::Add(Vector4 const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;
    m_Z += b.m_Z;
    m_W += b.m_W;

    return *this;
}

inline Vector4 const & Vector4::Subtract(Vector4 const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;
    m_Z -= b.m_Z;
    m_W -= b.m_W;

    return *this;
}

inline Vector4 const & Vector4::Scale(float scale)
{
    m_X *= scale;
    m_Y *= scale;
    m_Z *= scale;
    m_W *= scale;

    return *this;
}

inline Vector4 const & Vector4::operator +=(Vector4 const & b)
{
    return Add(b);
}

inline Vector4 const & Vector4::operator -=(Vector4 const & b)
{
    return Subtract(b);
}

inline Vector4 const & Vector4::operator *=(float scale)
{
    return Scale(scale);
}

//!
//! @note	In order to multiply, a 4th column with a value of [0, 0, 0, 1] is implicit.

inline Vector4 const & Vector4::operator *=(Matrix43 const & m)
{
    return Transform(m);
}

inline Vector4 const & Vector4::operator *=(Matrix44 const & m)
{
    return Transform(m);
}

inline Vector4 Vector4::operator -() const
{
    return Vector4(*this).Negate();
}

inline Vector4 Vector4::Origin()
{
    return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

inline Vector4 Vector4::XAxis()
{
    return Vector4(1.0f, 0.0f, 0.0f, 0.0f);
}

inline Vector4 Vector4::YAxis()
{
    return Vector4(0.0f, 1.0f, 0.0f, 0.0f);
}

inline Vector4 Vector4::ZAxis()
{
    return Vector4(0.0f, 0.0f, 1.0f, 0.0f);
}

inline Vector4 Vector4::WAxis()
{
    return Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

inline Vector4 operator +(Vector4 const & a, Vector4 const & b)
{
    return Vector4(a).Add(b);
}

inline Vector4 operator -(Vector4 const & a, Vector4 const & b)
{
    return Vector4(a).Subtract(b);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th column with a value of [0, 0, 0, 1] is implicit.

inline Vector4 operator *(Vector4 const & v, Matrix43 const & m)
{
    return Vector4(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th column with a value of [0, 0, 0, 1] is implicit.

inline Vector4 operator *(Matrix43 const & m, Vector4 const & v)
{
    return Vector4(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4 operator *(Vector4 const & v, Matrix44 const & m)
{
    return Vector4(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4 operator *(Matrix44 const & m, Vector4 const & v)
{
    return Vector4(v).Transform(m);
}

inline float Dot(Vector4 const & a, Vector4 const & b)
{
    return a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z + a.m_W * b.m_W;
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4 operator *(Vector4 const & v, float s)
{
    return Vector4(v).Scale(s);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector4 operator *(float s, Vector4 const & v)
{
    return Vector4(v).Scale(s);
}

#endif // !defined(MYMATH_VECTOR4_H)
