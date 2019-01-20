#pragma once

#if !defined(MYMATH_QUATERNION_H)
#define MYMATH_QUATERNION_H

#include <iosfwd>

class Matrix33;
class Vector3;

//! @defgroup	Quaternions		Quaternions
//!
//@{

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A quaternion.

class Quaternion
{
public:

    //! Constructor
    Quaternion() = default;

    //! Constructor
    Quaternion(float x, float y, float z, float w);

    //! Constructor
    Quaternion(float const q[4]);

    //! Constructor
    Quaternion(Vector3 const & axis, float angle);

    //! Constructor
    Quaternion(float yaw, float pitch, float roll);

    //! Conversion
    explicit Quaternion(Matrix33 const & m33);

    //! Returns an equivalent rotation matrix.
    Matrix33 GetRotationMatrix33() const;

    //! Returns an equivalent rotation axis and angle.
    void GetRotationAxisAndAngle(Vector3 * pAxis, float * pAngle) const;

    //! Returns the length of the quaternion squared.
    float Length2() const;

    //! Returns the length of the quaternion.
    float Length() const;

    //! Returns the inverse of the length of the quaternion (or 1 if the length is 0).
    float ILength() const;

    //! Returns the inverse of the length squared of the quaternion (or 1 if the length is 0).
    float ILength2() const;

    //! Returns true if the quaternion is normalized (within a tolerance).
    bool IsNormalized() const;

    //! Returns the result of raising the quaternion to a power.
    Quaternion Pow(float b) const;

    //! Normalizes the quaternion. Returns the result.
    Quaternion const & Normalize();

    //! Replaces the quaternion with its conjugate. Returns the result.
    Quaternion const & Conjugate();

    //! Adds a quaternion. Returns the result.
    Quaternion const & Add(Quaternion const & b);

    //! Subtracts a quaternion. Returns the result.
    Quaternion const & Subtract(Quaternion const & b);

    //! Scales the quaternion. Returns the result.
    Quaternion const & Scale(float scale);

    //! Multiplies the quaternion. Returns the result.
    Quaternion const & Multiply(Quaternion const & b);

    //! Adds a quaternion. Returns the result.
    Quaternion const & operator +=(Quaternion const & b);

    //! Subtracts a quaternion. Returns the result.
    Quaternion const & operator -=(Quaternion const & b);

    //! Scales the quaternion. Returns the result.
    Quaternion const & operator *=(float scale);

    //! Multiplies the quaternion by another. Returns the result.
    Quaternion const & operator *=(Quaternion const & b);

    //! Returns the conjugate.
    Quaternion operator -() const;

    union
    {
        float m_Q[4];       //!< Elements as an array {x, y, z, w}
        struct
        {
            float /** */ m_X, m_Y, m_Z, m_W;
        };
    };

    //! Returns the multiplicative identity [0, 0, 0, 1].
    static Quaternion Identity();
};

#pragma warning( pop )

//! Returns the sum of @a a and @a b.
Quaternion operator +(Quaternion const & a, Quaternion const & b);

//! Returns the difference between @a a and @a b.
Quaternion operator -(Quaternion const & a, Quaternion const & b);

//! Returns the product of @a a and @a b.
Quaternion operator *(Quaternion const & a, Quaternion const & b);

//! Returns the result of scaling @a q by @a scale.
Quaternion operator *(Quaternion const & q, float scale);

//! Returns the result of scaling @a q by @a scale.
Quaternion operator *(float scale, Quaternion const & q);

//! Extracts a Quaternion from a stream
std::istream & operator >>(std::istream & in, Quaternion & q);

//! Inserts a Quaternion into a stream
std::ostream & operator <<(std::ostream & out, Quaternion const & q);

//@}

// Inline functions

#include "MyMath.h"

#include <cassert>
#include <cmath>

inline Quaternion::Quaternion(float x, float y, float z, float w)
    : m_X(x)
    , m_Y(y)
    , m_Z(z)
    , m_W(w)
{
}

inline Quaternion::Quaternion(float const q[4])
    : m_X(q[0])
    , m_Y(q[1])
    , m_Z(q[2])
    , m_W(q[3])
{
}

inline float Quaternion::Length2() const
{
    return m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W;
}

inline float Quaternion::Length() const
{
    return sqrtf(Length2());
}

inline float Quaternion::ILength() const
{
    float const len = Length();

    assert(!MyMath::IsCloseToZero(len));

    return !MyMath::IsCloseToZero(len) ? 1.0f / len : 1.0f;
}

inline float Quaternion::ILength2() const
{
    float const len2 = Length2();

    assert(!MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_FLOAT_TOLERANCE));

    return !MyMath::IsCloseToZero(len2, 2.0 * MyMath::DEFAULT_FLOAT_TOLERANCE) ? 1.0f / len2 : 1.0f;
}

inline bool Quaternion::IsNormalized() const
{
    return MyMath::IsCloseTo(Length2(), 1.0, 2.0 * MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE);
}

inline Quaternion const & Quaternion::Normalize()
{
    return Scale(ILength());
}

inline Quaternion const & Quaternion::Conjugate()
{
    m_X = -m_X;
    m_Y = -m_Y;
    m_Z = -m_Z;
//	m_W = m_W;

    return *this;
}

inline Quaternion const & Quaternion::Add(Quaternion const & b)
{
    m_X += b.m_X;
    m_Y += b.m_Y;
    m_Z += b.m_Z;
    m_W += b.m_W;

    return *this;
}

inline Quaternion const & Quaternion::Subtract(Quaternion const & b)
{
    m_X -= b.m_X;
    m_Y -= b.m_Y;
    m_Z -= b.m_Z;
    m_W -= b.m_W;

    return *this;
}

inline Quaternion const & Quaternion::Scale(float scale)
{
    m_X *= scale;
    m_Y *= scale;
    m_Z *= scale;
    m_W *= scale;

    return *this;
}

inline Quaternion const & Quaternion::operator +=(Quaternion const & b)
{
    return Add(b);
}

inline Quaternion const & Quaternion::operator -=(Quaternion const & b)
{
    return Subtract(b);
}

inline Quaternion const & Quaternion::operator *=(float scale)
{
    return Scale(scale);
}

inline Quaternion const & Quaternion::operator *=(Quaternion const & b)
{
    return Multiply(b);
}

inline Quaternion Quaternion::operator -() const
{
    return Quaternion(*this).Conjugate();
}

inline Quaternion Quaternion::Identity()
{
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

inline Quaternion operator +(Quaternion const & a, Quaternion const & b)
{
    return Quaternion(a).Add(b);
}

inline Quaternion operator -(Quaternion const & a, Quaternion const & b)
{
    return Quaternion(a).Subtract(b);
}

//!
//! @warning	The operation is not commutative.

inline Quaternion operator *(Quaternion const & a, Quaternion const & b)
{
    return Quaternion(a).Multiply(b);
}

inline Quaternion operator *(Quaternion const & q, float s)
{
    return Quaternion(q).Scale(s);
}

inline Quaternion operator *(float s, Quaternion const & q)
{
    return Quaternion(q).Scale(s);
}

#endif // !defined(MYMATH_QUATERNION_H)
