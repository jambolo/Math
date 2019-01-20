#include "PrecompiledHeaders.h"

#include "Plane.h"

#include "Matrix43.h"
#include "Vector3.h"

Matrix43 Plane::GetReflectionMatrix() const
{
    float const xx =    -2.0f * (m_N.m_X * m_N.m_X);
    float const xy =    -2.0f * (m_N.m_X * m_N.m_Y);
    float const xz =    -2.0f * (m_N.m_X * m_N.m_Z);
    float const xd =    -2.0f * (m_N.m_X *     m_D);

    float const yy =    -2.0f * (m_N.m_Y * m_N.m_Y);
    float const yz =    -2.0f * (m_N.m_Y * m_N.m_Z);
    float const yd =    -2.0f * (m_N.m_Y *     m_D);

    float const zz =    -2.0f * (m_N.m_Z * m_N.m_Z);
    float const zd =    -2.0f * (m_N.m_Z *     m_D);

    return Matrix43(1.0f + xx,        xy,        xz,
                    xy, 1.0f + yy,        yz,
                    xz,        yz, 1.0f + zz,
                    xd,        yd,        zd);
}

Matrix43 Plane::GetProjectionMatrix() const
{
    float const xx =    -(m_N.m_X * m_N.m_X);
    float const xy =    -(m_N.m_X * m_N.m_Y);
    float const xz =    -(m_N.m_X * m_N.m_Z);
    float const xd =    -(m_N.m_X *     m_D);

    float const yy =    -(m_N.m_Y * m_N.m_Y);
    float const yz =    -(m_N.m_Y * m_N.m_Z);
    float const yd =    -(m_N.m_Y *     m_D);

    float const zz =    -(m_N.m_Z * m_N.m_Z);
    float const zd =    -(m_N.m_Z *     m_D);

    return Matrix43(1.0f + xx,        xy,        xz,
                    xy, 1.0f + yy,        yz,
                    xz,        yz, 1.0f + zz,
                    xd,        yd,        zd);
}

Matrix43 Plane::GetProjectionMatrix(Vector3 const & v) const
{
    assert(v.IsNormalized());
    assert(!MyMath::IsCloseToZero(Dot(m_N, v)));

    float const nDotV    = Dot(m_N, v);
    float const invNDotV = !MyMath::IsCloseToZero(nDotV) ? -1.0f / nDotV : -1.0f;

    float const vpx =   v.m_X * invNDotV;
    float const vpy =   v.m_Y * invNDotV;
    float const vpz =   v.m_Z * invNDotV;

    return Matrix43(1.0f + vpx * m_N.m_X,        vpy * m_N.m_X,        vpz * m_N.m_X,
                    vpx * m_N.m_Y, 1.0f + vpy * m_N.m_Y,        vpz * m_N.m_Y,
                    vpx * m_N.m_Z,        vpy * m_N.m_Z, 1.0f + vpz * m_N.m_Z,
                    vpx *     m_D,        vpy *     m_D,        vpz *     m_D);
}
