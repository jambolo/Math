#pragma once

#if !defined(MYMATH_VECTOR2_H)
#define MYMATH_VECTOR2_H

class Matrix22;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 2D vector of floats.
//
//! @ingroup Vectors
//!

class Vector2
{
public:

    //! Constructor
    Vector2() = default;

    //! Constructor
    Vector2(float x, float y);

    //! Constructor
    Vector2(float const v[2]);

    //! Returns the length of the vector squared.
    float Length2() const;

    //! Returns the length of the vector.
    float Length() const;

    //! Returns the inverse of the length of the vector (or 1 if the length is 0).
    float ILength() const;

    //! Returns the inverse of the length squared of the vector (or 1 if the length is 0).
    float ILength2() const;

    //! Returns true if the vector is normalized (within a tolerance).
    bool IsNormalized() const;

    //! Negates the vector. Returns the result.
    Vector2 const & Negate();

    //! Normalizes the vector. Returns the result.
    Vector2 const & Normalize();

    //! Adds a vector. Returns the result.
    Vector2 const & Add(Vector2 const & b);

    //! Subtracts a vector. Returns the result.
    Vector2 const & Subtract(Vector2 const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector2 const & Scale(float scale);

    //! Transforms the vector (vM). Returns the result.
    Vector2 const & Transform(Matrix22 const & m);

    //! Rotates the vector. Returns the result.
    Vector2 const & Rotate(float angle);

    //! Adds a vector. Returns the result.
    Vector2 const & operator +=(Vector2 const & b);

    //! Subtracts a vector. Returns the result.
    Vector2 const & operator -=(Vector2 const & b);

    //! Scales the vector. Returns the result.
    Vector2 const & operator *=(float scale);

    //! Transforms the vector (vM). Returns the result.
    Vector2 const & operator *=(Matrix22 const & m);

    //! Returns the negative.
    Vector2 operator -() const;

    union
    {
        float m_V[2];       //!< Elements as an array {x, y}
        struct
        {
            float /** */ m_X, m_Y;
        };
    };

    // Useful constants

    //! Returns [0, 0].
    static Vector2 Origin();

    //! Returns [1, 0].
    static Vector2 XAxis();

    //! Returns [0, 1].
    static Vector2 YAxis();
};

#pragma warning( pop )

//! @name Vector2 Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector2 operator +(Vector2 const & a, Vector2 const & b);

//! Returns the difference between @a a and @a b.
Vector2 operator -(Vector2 const & a, Vector2 const & b);

//! Returns the result of transforming @a v by @a m.
Vector2 operator *(Vector2 const & v, Matrix22 const & m);

//! Returns the result of transforming @a v by @a m.
Vector2 operator *(Matrix22 const & m, Vector2 const & v);

//! Returns the dot product of @a a and @a b.
float Dot(Vector2 const & a, Vector2 const & b);

//! Returns the result of scaling @a v by @a s.
Vector2 operator *(Vector2 const & v, float s);

//! Returns the result of scaling @a v by @a s.
Vector2 operator *(float s, Vector2 const & v);

//@}

// Inline functions

#include "MyMath.h"

#include <cassert>
#include <cmath>

inline Vector2::Vector2(float x, float y)
    : m_X(x)
    , m_Y(y)
{
}

inline Vector2::Vector2(float const v[2])
    : m_X(v[0])
    , m_Y(v[1])
{
}

inline float Vector2::Length2() const
{
    return m_X * m_X + m_Y * m_Y;

//  float	len;
//
//  __asm
//  {
//      femms
//      mov         eax,this
//      movq		mm0,[eax]
//      pfmul		mm0,mm0
//      pfacc		mm0,mm0
//      movd		len,mm0
//      femms
//  }
//
//  return len;
}

inline float Vector2::Length() const
{
    return sqrtf(Length2());

//  float	len;
//
//  __asm
//  {
//      femms
//      mov         eax,this
//      movq		mm0,[eax]
//      pfmul		mm0,mm0
//      pfacc		mm0,mm0
//      pfrsqrt     mm1,mm0
//      movq		mm2,mm1
//      pfmul		mm1,mm1
//      pfrsqit1	mm1,mm0
//      pfrcpit2	mm1,mm2
//      pfmul		mm0,mm1
//      movd		len,mm0
//      femms
//  }
//
//  return len;
}

inline float Vector2::ILength() const
{
    float const len = Length();

    assert(!MyMath::IsCloseToZero(len));

    return !MyMath::IsCloseToZero(len) ? 1.0f / len : 1.0f;

//  float	ilen;
//
//  __asm
//  {
//      femms
//      mov         eax,this
//      movq		mm0,[eax]
//      pfmul		mm0,mm0
//      pfacc		mm0,mm0
//      pfrsqrt     mm1,mm0
//      movq		mm2,mm1
//      pfmul		mm1,mm1
//      pfrsqit1	mm1,mm0
//      pfrcpit2	mm1,mm2
//      movd		ilen,mm1
//      femms
//  }
//
//  return ilen;
}

inline float Vector2::ILength2() const
{
    float const len2 = Length2();

    assert(!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));

    return (!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE)) ? 1.0f / len2 : 1.0f;

//  float	ilen2;
//
//  __asm
//  {
//      femms
//      mov         eax,this
//      movq		mm0,[eax]
//      pfmul		mm0,mm0
//      pfacc		mm0,mm0
//      pfrcp		mm1,mm0
//      pfrcpit1	mm0,mm1
//      pfrcpit2	mm0,mm1
//      movd		ilen2,mm0
//      femms
//  }
//
//  return ilen2;
}

inline bool Vector2::IsNormalized() const
{
    return MyMath::IsCloseTo(Length2(), 1.0, 2.0 * MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE);
}

inline Vector2 const & Vector2::Negate()
{
    m_X = -m_X;
    m_Y = -m_Y;

    return *this;
}

inline Vector2 const & Vector2::Normalize()
{
    return Scale(ILength());
}

inline Vector2 const & Vector2::Add(Vector2 const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;

    return *this;
}

inline Vector2 const & Vector2::Subtract(Vector2 const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;

    return *this;
}

inline Vector2 const & Vector2::Scale(float scale)
{
    m_X *= scale;
    m_Y *= scale;

    return *this;
}

inline Vector2 const & Vector2::operator +=(Vector2 const & b)
{
    return Add(b);
}

inline Vector2 const & Vector2::operator -=(Vector2 const & b)
{
    return Subtract(b);
}

inline Vector2 const & Vector2::operator *=(float scale)
{
    return Scale(scale);
}

inline Vector2 const & Vector2::operator *=(Matrix22 const & m)
{
    return Transform(m);
}

inline Vector2 Vector2::operator -() const
{
    return Vector2(*this).Negate();
}

inline Vector2 Vector2::Origin()
{
    return Vector2(0.0f, 0.0f);
}

inline Vector2 Vector2::XAxis()
{
    return Vector2(1.0f, 0.0f);
}

inline Vector2 Vector2::YAxis()
{
    return Vector2(0.0f, 1.0f);
}

inline Vector2 operator +(Vector2 const & a, Vector2 const & b)
{
    return Vector2(a).Add(b);
}

inline Vector2 operator -(Vector2 const & a, Vector2 const & b)
{
    return Vector2(a).Subtract(b);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2 operator *(Vector2 const & v, Matrix22 const & m)
{
    return Vector2(v).Transform(m);
}

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2 operator *(Matrix22 const & m, Vector2 const & v)
{
    return Vector2(v).Transform(m);
}

inline float Dot(Vector2 const & a, Vector2 const & b)
{
    return a.m_X * b.m_X + a.m_Y * b.m_Y;
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2 operator *(Vector2 const & v, float s)
{
    return Vector2(v).Scale(s);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2 operator *(float s, Vector2 const & v)
{
    return Vector2(v).Scale(s);
}

#endif // !defined(MYMATH_VECTOR2_H)
