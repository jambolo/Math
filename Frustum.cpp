#include "PrecompiledHeaders.h"

#include "Frustum.h"

#include "Plane.h"

Frustum::Frustum(Plane const & left, Plane const & right,
                 Plane const & bottom, Plane const & top,
                 Plane const & n, Plane const & f)
{
    m_Sides[LEFT_SIDE]   = left;
    m_Sides[RIGHT_SIDE]  = right;
    m_Sides[TOP_SIDE]    = top;
    m_Sides[BOTTOM_SIDE] = bottom;
    m_Sides[FRONT_SIDE]  = n;
    m_Sides[BACK_SIDE]   = f;
}
