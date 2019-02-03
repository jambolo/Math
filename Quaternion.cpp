#include "Quaternion.h"

#include "Matrix33.h"
#include "Matrix44.h"
#include "MyMath.h"
#include "Vector3.h"

#include <iostream>

Quaternion::Quaternion(Matrix33 const & m)
{
    float const trace = m.m_Xx + m.m_Yy + m.m_Zz;

    if (trace > 0.f)
    {
        float const sq = sqrtf(trace + 1.f);
        float const s  = 0.5f / sq;

        m_X = (m.m_Yz - m.m_Zy) * s;
        m_Y = (m.m_Zx - m.m_Xz) * s;
        m_Z = (m.m_Xy - m.m_Yx) * s;
        m_W = 0.5f * sq;
    }
    else
    {
        if (m.m_Xx >= m.m_Yy && m.m_Xx >= m.m_Zz)
        {
            float const sq = sqrtf(m.m_Xx - m.m_Yy - m.m_Zz + 1.0f);
            float const s  = 0.5f / sq;

            m_X = 0.5f * sq;
            m_Y = (m.m_Xy + m.m_Yx) * s;
            m_Z = (m.m_Zx + m.m_Xz) * s;
            m_W = (m.m_Yz - m.m_Zy) * s;
        }
        else if (m.m_Yy >= m.m_Xx && m.m_Yy >= m.m_Zz)
        {
            float const sq = sqrtf(-m.m_Xx + m.m_Yy - m.m_Zz + 1.0f);
            float const s  = 0.5f / sq;

            m_X = (m.m_Xy + m.m_Yx) * s;
            m_Y = 0.5f * sq;
            m_Z = (m.m_Yz + m.m_Zy) * s;
            m_W = (m.m_Zx - m.m_Xz) * s;
        }
        else // if ( m.m_Zz >= m.m_Xx && m.m_Zz >= m.m_Yy )
        {
            float const sq = sqrtf(-m.m_Xx - m.m_Yy + m.m_Zz + 1.0f);
            float const s  = 0.5f / sq;

            m_X = (m.m_Zx + m.m_Xz) * s;
            m_Y = (m.m_Yz + m.m_Zy) * s;
            m_Z = 0.5f * sq;
            m_W = (m.m_Xy - m.m_Yx) * s;
        }
    }
}

//! @param	axis	Axis of rotation
//! @param	angle	Angle of rotation
//!
//! @note	Do not confuse this with q( s, v ) notation.

Quaternion::Quaternion(Vector3 const & axis, float angle)
{
    assert(axis.IsNormalized());

    float const s = sinf(angle * 0.5f);
    float const c = cosf(angle * 0.5f);

    m_X = axis.m_X * s;
    m_Y = axis.m_Y * s;
    m_Z = axis.m_Z * s;
    m_W = c;
}

//! @param	yaw		Rotation angle (in radians) around the Y axis
//! @param	pitch	Rotation angle (in radians) around the X axis
//! @param	roll	Rotation angle (in radians) around the Z axis
//!
//! @note	The angles are applied in this order: @a yaw, @a pitch, then @a roll.

Quaternion::Quaternion(float yaw, float pitch, float roll)
{
    float const sr   = sinf(roll * 0.5f);
    float const cr   = cosf(roll * 0.5f);
    float const sp   = sinf(pitch * 0.5f);
    float const cp   = cosf(pitch * 0.5f);
    float const sy   = sinf(yaw * 0.5f);
    float const cy   = cosf(yaw * 0.5f);
    float const crsp = cr * sp;
    float const srsp = sr * sp;
    float const srcp = sr * cp;
    float const crcp = cr * cp;

//	*this    =   Quaternion( Vector3::ZAxis(), roll );
//	operator *=( Quaternion( Vector3::XAxis(), pitch ) );
//	operator *=( Quaternion( Vector3::YAxis(), yaw ) );

    m_X = crsp * cy - srcp * sy;
    m_Y = srsp * cy + crcp * sy;
    m_Z = srcp * cy + crsp * sy;
    m_W = crcp * cy - srsp * sy;
}

Matrix33 Quaternion::GetRotationMatrix33() const
{
    assert(IsNormalized());

    float const xx = m_X * m_X;
    float const xy = m_X * m_Y;
    float const xz = m_X * m_Z;
    float const xw = m_X * m_W;

    float const yy = m_Y * m_Y;
    float const yz = m_Y * m_Z;
    float const yw = m_Y * m_W;

    float const zz = m_Z * m_Z;
    float const zw = m_Z * m_W;

    return Matrix33(1.f - 2.f * (yy + zz),       2.f * (xy + zw),       2.f * (xz - yw),
                    2.f * (xy - zw), 1.f - 2.f * (xx + zz),       2.f * (yz + xw),
                    2.f * (xz + yw),       2.f * (yz - xw), 1.f - 2.f * (xx + yy));
}

//! @param	pAxis	Where to store the axis of rotation
//! @param	pAngle	Where to store the angle of rotation

void Quaternion::GetRotationAxisAndAngle(Vector3 * pAxis, float * pAngle) const
{
    assert(IsNormalized());

    float const w = MyMath::limit(-1.0f, m_W, 1.0f);        // Limit w so that acos() and sqrt() are happy
    float const s = sqrtf(1.f - w * w);             // = sin( .5 * 2. * acos( m_W ) );
                                                    // also = sqrt( m_X * m_X + m_Y * m_Y + m_Z * m_Z )
    if (!MyMath::IsCloseToZero(s))
    {
        pAxis->m_X = m_X / s;
        pAxis->m_Y = m_Y / s;
        pAxis->m_Z = m_Z / s;
    }
    else
    {
        *pAxis = Vector3::ZAxis();
    }

    *pAngle = 2.f * acosf(w);
}

//! The operation is (*this) ** t.
//!
//! @warning	This function only works for unit quaternions.

Quaternion Quaternion::Pow(float t) const
{
    assert(IsNormalized());

    // If q( w, V ) = q( cos(a), U*sin(a) ),
    //	then q( w, V )**t = q( cos(at), U*sin(at) )
    //					  = q( cos(at), U*sin(a)*sin(at)/sin(a) )
    //					  = q( cos(at), V*sin(at)/sin(a) )
    //
    // Note: if sin(a) == 0, then there is no rotation

    float const w  = MyMath::limit(-1.0f, m_W, 1.0f);       // Limit w so that acos() and sqrt() are happy
    float const sa = sqrtf(1.0f - w * w);           // = sin( acos( m_W ) ) = sin( a );

    if (!MyMath::IsCloseToZero(sa))
    {
        float const angle = acosf(w);
        float const satsa = sinf(angle * t) / sa;

        return Quaternion(m_X * satsa,          // m_X * sin( a * t ) / sin( a )
                          m_Y * satsa,          // m_Y * sin( a * t ) / sin( a )
                          m_Z * satsa,          // m_Z * sin( a * t ) / sin( a )
                          cosf(angle * t));     // cos( a * t )
    }
    else
    {
        return *this;
    }
}

//!
//! The operation is *this = *this * b

Quaternion const & Quaternion::Multiply(Quaternion const & b)
{
    Quaternion c;

    c.m_X = m_W * b.m_X + m_X * b.m_W + m_Y * b.m_Z - m_Z * b.m_Y;
    c.m_Y = m_W * b.m_Y - m_X * b.m_Z + m_Y * b.m_W + m_Z * b.m_X;
    c.m_Z = m_W * b.m_Z + m_X * b.m_Y - m_Y * b.m_X + m_Z * b.m_W;
    c.m_W = m_W * b.m_W - m_X * b.m_X - m_Y * b.m_Y - m_Z * b.m_Z;

    *this = c;

    return *this;
}

std::istream & operator >>(std::istream & in, Quaternion & q)
{
    in >> q.m_X >> q.m_Y >> q.m_Z >> q.m_W;

    return in;
}

std::ostream & operator <<(std::ostream & out, Quaternion const & q)
{
    out << q.m_X << ' ' << q.m_Y << ' ' << q.m_Z << ' ' << q.m_W;

    return out;
}
