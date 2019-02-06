#pragma once

#if !defined(MYMATH_VECTOR2I_H)
#define MYMATH_VECTOR2I_H

#include <iosfwd>

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 2D vector of integers.
//!
//! @ingroup Vectors
//!

class Vector2i
{
public:

    //! Constructor.
    Vector2i() = default;

    //! Constructor.
    Vector2i(int x, int y);

    //! Constructor.
    Vector2i(int const v[2]);

    //! Negates the vector. Returns the result.
    Vector2i const & Negate();

    //! Adds a vector. Returns the result.
    Vector2i const & Add(Vector2i const & b);

    //! Subtracts a vector. Returns the result.
    Vector2i const & Subtract(Vector2i const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector2i const & Scale(int scale);

    //! Adds a vector. Returns the result.
    Vector2i const & operator +=(Vector2i const & b);

    //! Subtracts a vector. Returns the result.
    Vector2i const & operator -=(Vector2i const & b);

    //! Scales the vector. Returns the result.
    Vector2i const & operator *=(int scale);

    //! Returns the negative.
    Vector2i operator -() const;

    union
    {
        int m_V[2];     //!< Elements as an array {x, y}
        struct
        {
            int /** */ m_X, m_Y;
        };
    };

    // Useful constants

    //! Returns [0, 0].
    static Vector2i Origin() { return { 0, 0 }; }

    //! Returns [1, 0].
    static Vector2i XAxis() { return { 1, 0 }; }

    //! Returns [0, 1].
    static Vector2i YAxis() { return { 0, 1 }; }
};

#pragma warning( pop )

//! @name Vector2i Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector2i operator +(Vector2i const & a, Vector2i const & b);

//! Returns the difference between @a a and @a b.
Vector2i operator -(Vector2i const & a, Vector2i const & b);

//! Returns the result of scaling @a v by @a s.
Vector2i operator *(Vector2i const & v, int s);

//! Returns the result of scaling @a v by @a s.
Vector2i operator *(int s, Vector2i const & v);

//@}

//! @name Vector3i Insert/Extract Operators
//! @ingroup Vectors
//@{

//! Extracts a Vector3i from a stream
std::istream & operator >>(std::istream & in, Vector2i & v);

//! Inserts a Vector3i into a stream
std::ostream & operator <<(std::ostream & out, Vector2i const & v);

//@}

// Inline functions

#include <cassert>
#include <cmath>

inline Vector2i::Vector2i(int x, int y)
    : m_X(x)
    , m_Y(y)
{
}

inline Vector2i::Vector2i(int const v[2])
    : m_X(v[0])
    , m_Y(v[1])
{
}

inline Vector2i const & Vector2i::Negate()
{
    m_X = -m_X;
    m_Y = -m_Y;

    return *this;
}

inline Vector2i const & Vector2i::Add(Vector2i const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;

    return *this;
}

inline Vector2i const & Vector2i::Subtract(Vector2i const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;

    return *this;
}

inline Vector2i const & Vector2i::Scale(int scale)
{
    m_X *= scale;
    m_Y *= scale;

    return *this;
}

inline Vector2i const & Vector2i::operator +=(Vector2i const & b)
{
    return Add(b);
}

inline Vector2i const & Vector2i::operator -=(Vector2i const & b)
{
    return Subtract(b);
}

inline Vector2i const & Vector2i::operator *=(int scale)
{
    return Scale(scale);
}

inline Vector2i Vector2i::operator -() const
{
    return Vector2i(*this).Negate();
}

inline Vector2i operator +(Vector2i const & a, Vector2i const & b)
{
    return Vector2i(a).Add(b);
}

inline Vector2i operator -(Vector2i const & a, Vector2i const & b)
{
    return Vector2i(a).Subtract(b);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2i operator *(Vector2i const & v, int s)
{
    return Vector2i(v).Scale(s);
}

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector2i operator *(int s, Vector2i const & v)
{
    return Vector2i(v).Scale(s);
}

#endif // !defined(MYMATH_VECTOR2I_H)
