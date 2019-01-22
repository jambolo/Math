#include "PrecompiledHeaders.h"

#include "Frustum.h"

#include "Plane.h"

Frustum::Frustum(Plane const & left, Plane const & right,
                 Plane const & bottom, Plane const & top,
                 Plane const & n, Plane const & f)
{
    sides_[LEFT_SIDE]   = left;
    sides_[RIGHT_SIDE]  = right;
    sides_[TOP_SIDE]    = top;
    sides_[BOTTOM_SIDE] = bottom;
    sides_[FRONT_SIDE]  = n;
    sides_[BACK_SIDE]   = f;
}
