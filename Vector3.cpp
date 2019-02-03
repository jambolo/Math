#include "Vector3.h"

#include "Matrix33.h"
#include "Matrix43.h"
#include "Quaternion.h"
#include "Vector3.h"

#include <iostream>

Vector3 const & Vector3::Transform(Matrix33 const & m)
{
    float const x = m_X;
    float const y = m_Y;
    float const z = m_Z;

//	m_X = x * m.m_Xx + y * m.m_Yx + z * m.m_Zx;
//	m_Y = x * m.m_Xy + y * m.m_Yy + z * m.m_Zy;
//	m_Z = x * m.m_Xz + y * m.m_Yz + z * m.m_Zz;

    // Optimized for cache coherency

    m_X = x * m.m_Xx;
    m_Y = x * m.m_Xy;
    m_Z = x * m.m_Xz;

    m_X += y * m.m_Yx;
    m_Y += y * m.m_Yy;
    m_Z += y * m.m_Yz;

    m_X += z * m.m_Zx;
    m_Y += z * m.m_Zy;
    m_Z += z * m.m_Zz;

    return *this;
}

//!
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

Vector3 const & Vector3::Transform(Matrix43 const & m)
{
    float const x = m_X;
    float const y = m_Y;
    float const z = m_Z;

//	m_X = x * m.m_Xx + y * m.m_Yx + z * m.m_Zx + 1.f * m.m_Tx;
//	m_Y = x * m.m_Xy + y * m.m_Yy + z * m.m_Zy + 1.f * m.m_Ty;
//	m_Z = x * m.m_Xz + y * m.m_Yz + z * m.m_Zz + 1.f * m.m_Tz;

    // Optimized for cache coherency

    m_X = x * m.m_Xx;
    m_Y = x * m.m_Xy;
    m_Z = x * m.m_Xz;

    m_X += y * m.m_Yx;
    m_Y += y * m.m_Yy;
    m_Z += y * m.m_Yz;

    m_X += z * m.m_Zx;
    m_Y += z * m.m_Zy;
    m_Z += z * m.m_Zz;

    m_X += m.m_Tx;
    m_Y += m.m_Ty;
    m_Z += m.m_Tz;

    return *this;
}

//!
//! @param	axis	Axis to rotate around
//! @param	angle	Angle of rotation

Vector3 const & Vector3::Rotate(Vector3 const & axis, float angle)
{
    assert(axis.IsNormalized());

    float const x = m_X;
    float const y = m_Y;
    float const z = m_Z;

    float const s  = sinf(angle);
    float const c  = cosf(angle);
    float const c1 = 1.f - c;

    float const xx = axis.m_X * axis.m_X * c1;
    float const xy = axis.m_X * axis.m_Y * c1;
    float const xz = axis.m_X * axis.m_Z * c1;
    float const xw = axis.m_X * s;

    float const yy = axis.m_Y * axis.m_Y * c1;
    float const yz = axis.m_Y * axis.m_Z * c1;
    float const yw = axis.m_Y * s;

    float const zz = axis.m_Z * axis.m_Z * c1;
    float const zw = axis.m_Z * s;

//	Matrix33 const	r( xx + c , xy - zw, xz + yw,
//					   xy + zw, yy + c , yz - xw,
//					   xz - yw, yz + xw, zz + c );
//
//	Transform( r );

    m_X = x * (xx + c) + y * (xy + zw) + z * (xz - yw);
    m_Y = x * (xy - zw) + y * (yy + c) + z * (yz + xw);
    m_Z = x * (xz + yw) + y * (yz - xw) + z * (zz + c);

    return *this;
}

Vector3 const & Vector3::Rotate(Quaternion const & q)
{
//	Transform( q.GetRotationMatrix33() );

    assert(q.IsNormalized());

    float const x = m_X;
    float const y = m_Y;
    float const z = m_Z;

    float const xx = q.m_X * q.m_X;
    float const xy = q.m_X * q.m_Y;
    float const xz = q.m_X * q.m_Z;
    float const xw = q.m_X * q.m_W;

    float const yy = q.m_Y * q.m_Y;
    float const yz = q.m_Y * q.m_Z;
    float const yw = q.m_Y * q.m_W;

    float const zz = q.m_Z * q.m_Z;
    float const zw = q.m_Z * q.m_W;

    m_X += 2.0f * (-x * (yy + zz) + y * (xy - zw) + z * (xz + yw));
    m_Y += 2.0f * (x * (xy + zw) - y * (xx + zz) + z * (yz - xw));
    m_Z += 2.0f * (x * (xz - yw) + y * (yz + xw) - z * (xx + yy));

    return *this;
}

float Dot(Vector3 const & a, Vector3 const & b)
{
    return a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z;
}

Vector3 Cross(Vector3 const & a, Vector3 const & b)
{
    return Vector3(a.m_Y * b.m_Z - a.m_Z * b.m_Y,
                   a.m_Z * b.m_X - a.m_X * b.m_Z,
                   a.m_X * b.m_Y - a.m_Y * b.m_X);
}

std::istream & operator >>(std::istream & in, Vector3 & v)
{
    in >> v.m_X >> v.m_Y >> v.m_Z;

    return in;
}

std::ostream & operator <<(std::ostream & out, Vector3 const & v)
{
    out << v.m_X << ' ' << v.m_Y << ' ' << v.m_Z;

    return out;
}
