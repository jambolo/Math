/** @file *//********************************************************************************************************

                                                  Intersectable.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Intersectable.cpp#20 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Intersectable.h"

#include "Box.h"
#include "Cone.h"
#include "Frustum.h"
#include "Line.h"
#include "MyMath.h"
#include "Plane.h"
#include "Point.h"
#include "Sphere.h"

#pragma warning( disable : 4100 )   // 'identifier' : unreferenced formal parameter

//! @param	a		The point to test.
//! @param	b		The point to test.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & a, Point const & b)
{
    if (  MyMath::IsRelativelyCloseTo(a.m_X, b.m_X)
       && MyMath::IsRelativelyCloseTo(a.m_Y, b.m_Y)
       && MyMath::IsRelativelyCloseTo(a.m_Z, b.m_Z))
    {
        return INTERSECTS;
    }
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test.
//! @param	line		The line to test.
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Line const & line)
{
//	// The point is on the line if the distance is close to 0
//
//	return MyMath::IsCloseToZero( line.Distance( point ) );
//
    // Yes, but also ...
    // point is on the line if the distance from m_B to point is the same as the distance from m_B to the projection
    // of point onto the line (which implies distance squared is a valid test, too).

    Vector3 const pb = point - line.m_B;        // Vector from m_B to point
    float const   d  = Dot(pb, line.m_M);       // Distance from m_B to the projection

    if (MyMath::IsRelativelyCloseTo(d * d, pb.Length2()))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test.
//! @param	ray			The ray to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Ray const & ray)
{
//	// The point is on the line if the distance is close to 0
//
//	return MyMath::IsCloseToZero( ray.Distance( point ) );
//
    // Yes, but also like the line ...
    // point is on the ray if the distance from m_B to point is the same as the distance from m_B to the projection
    // of point onto the line (which implies distance squared is a valid test, too), and t >= 0. Note that t is the
    // distance from m_B to the projection of point onto the line. Zoinks!

    Vector3 const pb = point - ray.m_B;         // Vector from m_B to point
    float const   t  = Dot(pb, ray.m_M);        // Also, distance from m_B to the projection

    if (t >= 0.f && MyMath::IsRelativelyCloseTo(t * t, pb.Length2()))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test
//! @param	segment	The segment to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Segment const & segment)
{
//	// The point is on the segment if the distance is close to 0
//
//	return MyMath::IsCloseToZero( segment.Distance( point ) );
//
    // Yes, but also like the line ...
    // point is on the ray if the distance from m_B to point is the same as the distance from m_B to the projection
    // of point onto the line (which implies distance squared is a valid test, too), and 0 <= t <= 1. Note that the
    // length of m_M is the length of the segment in this case. Yowzer! That means the math is simple but it is not
    // so obvious.

    Vector3 const pb = point - segment.m_B;         // Vector from m_B to point
    float const   s2 = segment.m_M.Length2();       // Length of segment squared
    float const   a  = Dot(pb, segment.m_M);        // t * s2

    if (a >= 0.f && a <= s2 && MyMath::IsRelativelyCloseTo(a * a, pb.Length2()))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test
//! @param	plane		The plane to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Plane const & plane)
{
    if (MyMath::IsCloseToZero(Distance(point, plane)))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test.
//! @param	poly		The poly to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Poly const & poly)
{
    return NO_INTERSECTION;
}

//! @param	point		The point to test
//! @param	sphere		The sphere to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Sphere const & sphere)
{
    float const d2 = (point - sphere.m_C).Length2();    // Distance from center to point squared

    if (d2 <= sphere.m_R * sphere.m_R)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test
//! @param	cone		The cone to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Cone const & cone)
{
    Vector3 const p   = point - cone.m_V;
    float const   ddp = Dot(cone.m_D, p);

    if (ddp >= 0.f && ddp * ddp >= p.Length2() * cone.m_A * cone.m_A)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test
//! @param	aabox		The AA box to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, AABox const & aabox)
{
    Vector3 const xpoint = point - aabox.m_Position;

    if (  0 <= xpoint.m_X && xpoint.m_X <= aabox.m_Scale.m_X
       && 0 <= xpoint.m_Y && xpoint.m_Y <= aabox.m_Scale.m_Y
       && 0 <= xpoint.m_Z && xpoint.m_Z <= aabox.m_Scale.m_Z)
    {
        return INTERSECTS;
    }
    else
        return NO_INTERSECTION;
}

//! @param	point	The point to test
//! @param	box		The oriented box to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Box const & box)
{
    Vector3 const xpoint = box.m_InverseOrientation * (point - box.m_Position);

    if (  0 <= xpoint.m_X && xpoint.m_X <= box.m_Scale.m_X
       && 0 <= xpoint.m_Y && xpoint.m_Y <= box.m_Scale.m_Y
       && 0 <= xpoint.m_Z && xpoint.m_Z <= box.m_Scale.m_Z)
    {
        return INTERSECTS;
    }
    else
        return NO_INTERSECTION;
}

//! @param	point		The point to test
//! @param	frustum		The frustum to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, Frustum const & frustum)
{
    for (int i = 0; i < Frustum::NUM_SIDES; i++)
    {
        if (frustum.m_Sides[i].DirectedDistance(point) > 0.f)
            return NO_INTERSECTION;
    }

    return INTERSECTS;
}

//! @param	a		The line to test
//! @param	b		The line to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Line const & a, Line const & b)
{
    if (MyMath::IsCloseToZero(Distance(a, b)))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	line		The line to test.
//! @param	ray			The ray to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Ray const & ray)
{
    return NO_INTERSECTION;
}

//! @param	line		The line to test.
//! @param	segment		The segment to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Segment const & segment)
{
    return NO_INTERSECTION;
}

//! @param	line		The line to test
//! @param	plane		The plane to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Plane const & plane)
{
    if (!MyMath::IsCloseToZero(Dot(line.m_M, plane.m_N)))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	line		The line to test.
//! @param	poly		The poly to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Poly const & poly)
{
    return NO_INTERSECTION;
}

//! @param	line		The line to test
//! @param	sphere		The sphere to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Sphere const & sphere)
{
    if (Distance(sphere.m_C, line) <= sphere.m_R)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	line		The line to test.
//! @param	cone		The cone to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Cone const & cone)
{
    return NO_INTERSECTION;
}

//! @param	line		The line to test
//! @param	aabox		The AA box to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, AABox const & aabox)
{
    Vector3 const box_max = aabox.m_Position + aabox.m_Scale;   // Convenience and speed

    // If the line intersects the yz planes, check each plane to see if any intersection is within the box

    if (!MyMath::IsCloseToZero(line.m_M.m_X))
    {
        // Check the min yz plane

        float const umin = (aabox.m_Position.m_X - line.m_B.m_X) / line.m_M.m_X;
        float const ymin = line.m_B.m_Y + umin * line.m_M.m_Y;
        float const zmin = line.m_B.m_Z + umin * line.m_M.m_Z;

        if (  ymin >= aabox.m_Position.m_Y && ymin <= box_max.m_Y
           && zmin >= aabox.m_Position.m_Z && zmin <= box_max.m_Z)
        {
            return INTERSECTS;
        }

        // Check the max yz plane

        float const umax = (box_max.m_X - line.m_B.m_X) / line.m_M.m_X;
        float const ymax = line.m_B.m_Y + umax * line.m_M.m_Y;
        float const zmax = line.m_B.m_Z + umax * line.m_M.m_Z;

        if (  ymax >= aabox.m_Position.m_Y && ymax <= box_max.m_Y
           && zmax >= aabox.m_Position.m_Z && zmax <= box_max.m_Z)
        {
            return INTERSECTS;
        }
    }

    // If the line intersects the xz planes, check each plane to see if any intersection is within the box

    if (!MyMath::IsCloseToZero(line.m_M.m_Y))
    {
        // Check the min xz plane

        float const umin = (aabox.m_Position.m_Y - line.m_B.m_Y) / line.m_M.m_Y;
        float const xmin = line.m_B.m_X + umin * line.m_M.m_X;
        float const zmin = line.m_B.m_Z + umin * line.m_M.m_Z;

        if (  xmin >= aabox.m_Position.m_X && xmin <= box_max.m_X
           && zmin >= aabox.m_Position.m_Z && zmin <= box_max.m_Z)
        {
            return INTERSECTS;
        }

        // Check the max xz plane

        float const umax = (box_max.m_Y - line.m_B.m_Y) / line.m_M.m_Y;
        float const xmax = line.m_B.m_X + umax * line.m_M.m_X;
        float const zmax = line.m_B.m_Z + umax * line.m_M.m_Z;

        if (  xmax >= aabox.m_Position.m_X && xmax <= box_max.m_X
           && zmax >= aabox.m_Position.m_Z && zmax <= box_max.m_Z)
        {
            return INTERSECTS;
        }
    }

    // If the line intersects the xy planes, check each plane to see if any intersection is within the box

    if (!MyMath::IsCloseToZero(line.m_M.m_Z))
    {
        // Check the min xy plane

        float const umin = (aabox.m_Position.m_Z - line.m_B.m_Z) / line.m_M.m_Z;
        float const xmin = line.m_B.m_X + umin * line.m_M.m_X;
        float const ymin = line.m_B.m_Y + umin * line.m_M.m_Y;

        if (  xmin >= aabox.m_Position.m_X && xmin <= box_max.m_X
           && ymin >= aabox.m_Position.m_Y && ymin <= box_max.m_Y)
        {
            return INTERSECTS;
        }

        // Check the max xy plane

        float const umax = (box_max.m_Z - line.m_B.m_Z) / line.m_M.m_Z;
        float const xmax = line.m_B.m_X + umax * line.m_M.m_X;
        float const ymax = line.m_B.m_Y + umax * line.m_M.m_Y;

        if (  xmax >= aabox.m_Position.m_X && xmax <= box_max.m_X
           && ymax >= aabox.m_Position.m_Y && ymax <= box_max.m_Y)
        {
            return INTERSECTS;
        }
    }

    return NO_INTERSECTION;
}

//! @param	line	The line to test
//! @param	box		The oriented box to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Box const & box)
{
    // Transform the line into the box's space (except for scale)

    Vector3 const tb = box.m_InverseOrientation * (line.m_B - box.m_Position);
    Vector3 const tm = box.m_InverseOrientation * line.m_M;

    // If the line intersects the yz planes, check each plane to see if any intersection is within the box

    if (!MyMath::IsCloseToZero(tm.m_X))
    {
        // Check the min yz plane

        float const umin = (0.f - tb.m_X) / tm.m_X;
        float const ymin = tb.m_Y + umin * tm.m_Y;
        float const zmin = tb.m_Z + umin * tm.m_Z;

        if (ymin >= 0.f && ymin <= box.m_Scale.m_Y && zmin >= 0.f && zmin <= box.m_Scale.m_Z)
            return INTERSECTS;

        // Check the max yz plane

        float const umax = (box.m_Scale.m_X - tb.m_X) / tm.m_X;
        float const ymax = tb.m_Y + umax * tm.m_Y;
        float const zmax = tb.m_Z + umax * tm.m_Z;

        if (ymax >= 0.f && ymax <= box.m_Scale.m_Y && zmax >= 0.f && zmax <= box.m_Scale.m_Z)
            return INTERSECTS;
    }

    // If the line intersects the xz planes, check each plane to see if any intersection is within the box

    if (!MyMath::IsCloseToZero(tm.m_Y))
    {
        // Check the min xz plane

        float const umin = (0.f - tb.m_Y) / tm.m_Y;
        float const xmin = tb.m_X + umin * tm.m_X;
        float const zmin = tb.m_Z + umin * tm.m_Z;

        if (xmin >= 0.f && xmin <= box.m_Scale.m_X && zmin >= 0.f && zmin <= box.m_Scale.m_Z)
            return INTERSECTS;

        // Check the max xz plane

        float const umax = (box.m_Scale.m_Y - tb.m_Y) / tm.m_Y;
        float const xmax = tb.m_X + umax * tm.m_X;
        float const zmax = tb.m_Z + umax * tm.m_Z;

        if (xmax >= 0.f && xmax <= box.m_Scale.m_X && zmax >= 0.f && zmax <= box.m_Scale.m_Z)
            return INTERSECTS;
    }

    // If the line intersects the xy planes, check each plane to see if any intersection is within the box

    if (!MyMath::IsCloseToZero(tm.m_Z))
    {
        // Check the min xy plane

        float const umin = (0.f - tb.m_Z) / tm.m_Z;
        float const xmin = tb.m_X + umin * tm.m_X;
        float const ymin = tb.m_Y + umin * tm.m_Y;

        if (xmin >= 0.f && xmin <= box.m_Scale.m_X && ymin >= 0.f && ymin <= box.m_Scale.m_Y)
            return INTERSECTS;

        // Check the max xy plane

        float const umax = (box.m_Scale.m_Z - tb.m_Z) / tm.m_Z;
        float const xmax = tb.m_X + umax * tm.m_X;
        float const ymax = tb.m_Y + umax * tm.m_Y;

        if (xmax >= 0.f && xmax <= box.m_Scale.m_X && ymax >= 0.f && ymax <= box.m_Scale.m_Y)
            return INTERSECTS;
    }

    return NO_INTERSECTION;
}

//! @param	line		The line to test.
//! @param	frustum		The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a		The ray to test.
//! @param	b		The ray to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & a, Ray const & b)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	segment		The segment to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Segment const & segment)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	plane		The plane to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Plane const & plane)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	poly		The poly to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Poly const & poly)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	sphere		The sphere to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Sphere const & sphere)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	cone			The cone to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Cone const & cone)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	aabox		The AA box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, AABox const & aabox)
{
    return NO_INTERSECTION;
}

//! @param	ray		The ray to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	ray			The ray to test.
//! @param	frustum		The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a	The line segment to test
//! @param	b	The line segment to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & a, Segment const & b)
{
    // First of all, reject if the AABoxes don't intersect.

    if (Intersectable::Intersects(AABox(a.m_B, a.m_M), AABox(b.m_B, b.m_M)) == NO_INTERSECTION)
        return NO_INTERSECTION;

// The line segments a and b intersect if 0<=s<=1 and 0<=t<=1 when a.m_B + s * a.m_M == b.m_B + t * b.m_M.
//
// Solving for s and t:
//
//		a.m_B + s * a.m_M = b.m_B + t * b.m_M
//		a.m_B - b.m_B = t * b.m_M - s * a.m_M
//		c = t * b.m_M - s * a.m_M, c = a.m_B - b.m_B
//
//		c.x = t * b.m_M.m_X - s * a.m_M.m_X
//		c.y = t * b.m_M.m_Y - s * a.m_M.m_Y
//		c.z = t * b.m_M.m_Z - s * a.m_M.m_Z
//
//		sxy = ( c.x * b.m_M.m_Y - c.y * b.m_M.m_X ) / ( b.m_M.m_X * a.m_M.m_Y - b.m_M.m_Y * a.m_M.m_X )
//		txy = ( c.x * a.m_M.m_Y - c.y * a.m_M.m_X ) / ( b.m_M.m_X * a.m_M.m_Y - b.m_M.m_Y * a.m_M.m_X )
//		sxz = ( c.x * b.m_M.m_Z - c.z * b.m_M.m_X ) / ( b.m_M.m_X * a.m_M.m_Z - b.m_M.m_Z * a.m_M.m_X )
//		txz = ( c.x * a.m_M.m_Z - c.z * a.m_M.m_X ) / ( b.m_M.m_X * a.m_M.m_Z - b.m_M.m_Z * a.m_M.m_X )
//		syz = ( c.y * b.m_M.m_Z - c.z * b.m_M.m_Y ) / ( b.m_M.m_Y * a.m_M.m_Z - b.m_M.m_Z * a.m_M.m_Y )
//		tyz = ( c.y * a.m_M.m_Z - c.z * a.m_M.m_Y ) / ( b.m_M.m_Y * a.m_M.m_Z - b.m_M.m_Z * a.m_M.m_Y )
//
// The segments intersect if sxy == sxz == syz and txy == txz == tyz, and 0<=s<=1 and 0<=t<=1, s = sxy and t = txy.
//
// Ideally only two of each of the three computations need to be checked, because the third is redundant. Rather
// than just picking two, all three are checked and the segments are considered to intersect if two of the three
// pass. Also, the division is never done -- it is integrated into the range test. These steps avoid precision
// problems and divide-by-0 when one or both segments are (nearly) parallel to an axis.

    Vector3 const c    = a.m_B - b.m_B;
    int           pass = 0;         // Number of tests that pass

    // Check if they intersect in the xy plane.

    float const sxy = (c.m_X * b.m_M.m_Y - c.m_Y * b.m_M.m_X);
    float const txy = (c.m_X * a.m_M.m_Y - c.m_Y * a.m_M.m_X);
    float const dxy = b.m_M.m_X * a.m_M.m_Y - b.m_M.m_Y * a.m_M.m_X;

    if (dxy > 0.f)
    {
        if (sxy >= 0.f && sxy <= dxy && txy >= 0 && txy <= dxy)
            ++pass;
    }
    else
    {
        if (sxy <= 0.f && sxy >= dxy && txy <= 0 && txy >= dxy)
            ++pass;
    }

    // Check if they intersect in the xz plane.

    float const sxz = (c.m_X * b.m_M.m_Z - c.m_Z * b.m_M.m_X);
    float const txz = (c.m_X * a.m_M.m_Z - c.m_Z * a.m_M.m_X);
    float const dxz = b.m_M.m_X * a.m_M.m_Z - b.m_M.m_Z * a.m_M.m_X;

    if (dxz > 0.f)
    {
        if (sxz >= 0.f && sxz <= dxz && txz >= 0 && txz <= dxz)
            ++pass;
    }
    else
    {
        if (sxz <= 0.f && sxz >= dxz && txz <= 0 && txz >= dxz)
            ++pass;
    }

    // Check if they intersect in the yz plane.
    // The third test is needed only if one of the previous passed and one failed.

    if (pass == 1)
    {
        float const syz = (c.m_Y * b.m_M.m_Z - c.m_Z * b.m_M.m_Y);
        float const tyz = (c.m_Y * a.m_M.m_Z - c.m_Z * a.m_M.m_Y);
        float const dyz = b.m_M.m_Y * a.m_M.m_Z - b.m_M.m_Z * a.m_M.m_Y;

        if (dyz > 0.f)
        {
            if (syz >= 0.f && syz <= dyz && tyz >= 0 && tyz <= dyz)
                ++pass;
        }
        else
        {
            if (syz <= 0.f && syz >= dyz && tyz <= 0 && tyz >= dyz)
                ++pass;
        }
    }

    if (pass >= 2)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	plane	The plane to test.
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, Plane const & plane)
{
    float const da = plane.DirectedDistance(segment.m_B);
    float const db = plane.DirectedDistance(segment.m_B + segment.m_M);
    if (MyMath::IsCloseToZero(da) || MyMath::IsCloseToZero(db) || da * db < 0.f)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	poly	The poly to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, Poly const & poly)
{
    return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	sphere	The sphere to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, Sphere const & sphere)
{
    return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	cone	The cone to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, Cone const & cone)
{
    return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	aabox	The line AA box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, AABox const & aabox)
{
    return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	segment	The line segment to test.
//! @param	frustum	The line frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a	The plane to test
//! @param	b	The plane to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & a, Plane const & b)
{
    float const dot = Dot(a.m_N, b.m_N);

    if (!MyMath::IsCloseTo(fabsf(dot), 1.0))
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	plane	The plane to test.
//! @param	poly	The poly to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, Poly const & poly)
{
    return NO_INTERSECTION;
}

//! @param	plane	The plane to test.
//! @param	sphere	The sphere to test.
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, Sphere const & sphere)
{
    if (Distance(sphere.m_C, plane) <= sphere.m_R)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	plane	The plane to test.
//! @param	cone	The cone to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, Cone const & cone)
{
    return NO_INTERSECTION;
}

//! @param	plane	The plane to test.
//! @param	aabox	The AA box to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, AABox const & aabox)
{
    HalfSpace const halfspace(plane);

    if (Intersects(halfspace, aabox) == INTERSECTS)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	plane	The plane to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, Box const & box)
{
//	// Plane equation:  z = - ( plane.m_D + plane.m_N.m_X * x + plane.m_N.m_Y * y ) / plane.m_N.m_Z

//	if ( !MyMath::IsCloseToZero( plane.m_N.m_X )
//	{
//		float const	yy	= plane.m_N.m_X * box.m_X;
//		float const	yyh	= plane.m_N.m_X * ( box.m_X + box.m_W );
//		float const	zz	= plane.m_N.m_Z * box.m_Z;
//		float const	zzd	= plane.m_N.m_Z * ( box.m_Z + box.m_D );
//		float const	xw	= box.m_X + box.m_W;
//		float		x;

//		x = - ( plane.m_D + yy + zz ) / plane.m_N.m_X;
//		if ( box.m_X <= x && x <= xw )
//		{
//			return INTERSECTS;
//		}

//		x = - ( plane.m_D + yyh + zz ) / plane.m_N.m_X;
//		if ( box.m_X <= x && x <= xw )
//		{
//			return INTERSECTS;
//		}

//		x = - ( plane.m_D + yy + zzd ) / plane.m_N.m_X;
//		if ( box.m_X <= x && x <= xw )
//		{
//			return INTERSECTS;
//		}

//		x = - ( plane.m_D + yyh + zzd ) / plane.m_N.m_X;
//		if ( box.m_X <= x && x <= xw )
//		{
//			return INTERSECTS;
//		}
//	}

//	if ( !MyMath::IsCloseToZero( plane.m_N.m_Y )
//	{
//		float const	xx	= plane.m_N.m_X * box.m_X;
//		float const	xxw	= plane.m_N.m_X * ( box.m_X + box.m_W );
//		float const	zz	= plane.m_N.m_Z * box.m_Z;
//		float const	zzd	= plane.m_N.m_Z * ( box.m_Z + box.m_D );
//		float const	yh	= box.m_Y + box.m_H;
//		float		y;

//		y = - ( plane.m_D + xx + zz ) / plane.m_N.m_Y;
//		if ( box.m_Y <= y && y <= yh )
//		{
//			return INTERSECTS;
//		}

//		y = - ( plane.m_D + xxw + zz ) / plane.m_N.m_Y;
//		if ( box.m_Y <= y && y <= yh )
//		{
//			return INTERSECTS;
//		}

//		y = - ( plane.m_D + xx + zzd ) / plane.m_N.m_Y;
//		if ( box.m_Y <= y && y <= yh )
//		{
//			return INTERSECTS;
//		}

//		y = - ( plane.m_D + xxw + zzd ) / plane.m_N.m_Y;
//		if ( box.m_Y <= y && y <= yh )
//		{
//			return INTERSECTS;
//		}
//	}

//	if ( !MyMath::IsCloseToZero( plane.m_N.m_Z )
//	{
//		float const	xx	= plane.m_N.m_X * box.m_X;
//		float const	xxw	= plane.m_N.m_X * ( box.m_X + box.m_W );
//		float const	yy	= plane.m_N.m_Y * box.m_Y;
//		float const	yyh	= plane.m_N.m_Y * ( box.m_Y + box.m_H );
//		float const	zd	= box.m_Z + box.m_D;
//		float		z;

//		z = - ( plane.m_D + xx + yy ) / plane.m_N.m_Z;
//		if ( box.m_Z <= z && z <= zd )
//		{
//			return INTERSECTS;
//		}

//		z = - ( plane.m_D + xxw + yy ) / plane.m_N.m_Z;
//		if ( box.m_Z <= z && z <= zd )
//		{
//			return INTERSECTS;
//		}

//		z = - ( plane.m_D + xx + yyh ) / plane.m_N.m_Z;
//		if ( box.m_Z <= z && z <= zd )
//		{
//			return INTERSECTS;
//		}

//		z = - ( plane.m_D + xxw + yyh ) / plane.m_N.m_Z;
//		if ( box.m_Z <= z && z <= zd )
//		{
//			return INTERSECTS;
//		}
//	}

    return NO_INTERSECTION;
}

//! @param	plane	The plane to test.
//! @param	frustum	The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a	The poly to test.
//! @param	b	The poly to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Poly const & a, Poly const & b)
{
    return NO_INTERSECTION;
}

//! @param	poly	The poly to test.
//! @param	sphere	The sphere to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Poly const & poly, Sphere const & sphere)
{
    return NO_INTERSECTION;
}

//! @param	poly	The poly to test.
//! @param	cone	The cone to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Poly const & poly, Cone const & cone)
{
    return NO_INTERSECTION;
}

//! @param	poly	The poly to test.
//! @param	aabox	The AA box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Poly const & poly, AABox const & aabox)
{
    return NO_INTERSECTION;
}

//! @param	poly	The poly to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Poly const & poly, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	poly	The poly to test.
//! @param	frustum	The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Poly const & poly, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a	The sphere to test.
//! @param	b	The sphere to test.
//!
//! @return		Returns NO_INTERSECTION, INTERSECTS, ENCLOSES, or ENCLOSED_BY.

Intersectable::IntersectionClass Intersectable::Intersects(Sphere const & a, Sphere const & b)
{
    float const dc2 = (a.m_C - b.m_C).Length2();

    if (dc2 <= (a.m_R + b.m_R) * (a.m_R + b.m_R))
    {
        if (dc2 <= (a.m_R - b.m_R) * (a.m_R - b.m_R))
        {
            if (a.m_R < b.m_R)
                return ENCLOSED_BY;
            else
                return ENCLOSES;
        }
        else
        {
            return INTERSECTS;
        }
    }
    else
    {
        return NO_INTERSECTION;
    }
}

//! @param	sphere	The sphere to test.
//! @param	cone	The cone to test.
//!
//! @return		Returns NO_INTERSECTION, INTERSECTS, ENCLOSES, or ENCLOSED_BY.
//!
//! @warning	Not sure if this works

Intersectable::IntersectionClass Intersectable::Intersects(Sphere const & sphere, Cone const & cone)
{
    float const   c2   = cone.m_A * cone.m_A;
    Vector3 const v1   = sphere.m_C - cone.m_V;
    Vector3 const v2   = sqrtf(1.f - c2) * v1 + sphere.m_R * cone.m_D;
    float const   ddv2 = Dot(cone.m_D, v2);

    if (ddv2 < 0.f || ddv2 * ddv2 < v2.Length2() * c2)
        return NO_INTERSECTION;

    float const ddv1 = Dot(cone.m_D, v1);
    float const ld2  = v1.Length2();

    if (ddv1 > 0.f || ddv1 * ddv1 < ld2 * (1.f - c2) || ld2 <= sphere.m_R * sphere.m_R)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	sphere	The sphere to test.
//! @param	aabox	The AA box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Sphere const & sphere, AABox const & aabox)
{
    return NO_INTERSECTION;
}

//! @param	sphere	The sphere to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Sphere const & sphere, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	sphere	The sphere to test.
//! @param	frustum	The frustum to test
//!
//! @return		Returns NO_INTERSECTION, INTERSECTS, ENCLOSES, or ENCLOSED_BY.
//!
//! @warning	This test returns false positives near the corners of the frustum.
//! @warning	This function returns INTERSECTS when it should return ENCLOSES.

Intersectable::IntersectionClass Intersectable::Intersects(Sphere const & sphere, Frustum const & frustum)
{
    IntersectionClass intersection = ENCLOSED_BY;
    for (int i = 0; i < Frustum::NUM_SIDES; i++)
    {
        float const d = frustum.m_Sides[i].DirectedDistance(sphere.m_C);

        if (d > sphere.m_R)
            return NO_INTERSECTION;
        if (d > -sphere.m_R)
            intersection = INTERSECTS;
    }

    return intersection;
}

//! @param	a	The cone to test.
//! @param	b	The cone to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Cone const & a, Cone const & b)
{
    return NO_INTERSECTION;
}

//! @param	cone	The cone to test.
//! @param	aabox	The AA box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Cone const & cone, AABox const & aabox)
{
    return NO_INTERSECTION;
}

//! @param	cone	The cone to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Cone const & cone, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	cone	The cone to test.
//! @param	frustum	The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Cone const & cone, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a	The AABox to test.
//! @param	b	The AABox to test.
//!
//! @return		Returns NO_INTERSECTION, INTERSECTS, ENCLOSES, or ENCLOSED_BY.

Intersectable::IntersectionClass Intersectable::Intersects(AABox const & a, AABox const & b)
{
    float const ax0 = a.m_Position.m_X;
    float const ay0 = a.m_Position.m_Y;
    float const az0 = a.m_Position.m_Z;
    float const ax1 = a.m_Position.m_X + a.m_Scale.m_X;
    float const ay1 = a.m_Position.m_Y + a.m_Scale.m_Y;
    float const az1 = a.m_Position.m_Z + a.m_Scale.m_Z;
    float const bx0 = b.m_Position.m_X;
    float const by0 = b.m_Position.m_Y;
    float const bz0 = b.m_Position.m_Z;
    float const bx1 = b.m_Position.m_X + b.m_Scale.m_X;
    float const by1 = b.m_Position.m_Y + b.m_Scale.m_Y;
    float const bz1 = b.m_Position.m_Z + b.m_Scale.m_Z;

    assert(a.m_Scale.m_X >= 0.0f);
    assert(a.m_Scale.m_Y >= 0.0f);
    assert(a.m_Scale.m_Z >= 0.0f);
    assert(b.m_Scale.m_X >= 0.0f);
    assert(b.m_Scale.m_Y >= 0.0f);
    assert(b.m_Scale.m_Z >= 0.0f);

    if (ax0 <= bx1 && bx0 <= ax1 && ay0 <= by1 && by0 <= ay1 && az0 <= bz1 && bz0 <= az1)
    {
        if (bx0 <= ax0 && ax1 <= bx1 && by0 <= ay0 && ay1 <= by1 && bz0 <= az0 && az1 <= bz1)
            return ENCLOSED_BY;
        else if (ax0 <= bx0 && bx1 <= ax1 && ay0 <= by0 && by1 <= ay1 && az0 <= bz0 && bz1 <= az1)
            return ENCLOSES;
        else
            return INTERSECTS;
    }
    else
    {
        return NO_INTERSECTION;
    }
}

//! @param	aabox	The AABox to test.
//! @param	box		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(AABox const & aabox, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	aabox	The AABox to test.
//! @param	frustum	The frustum to test.
//!
//! @return		Returns NO_INTERSECTION, INTERSECTS, or ENCLOSED_BY
//!
//! @warning	Returns INTERSECTS when it should return ENCLOSES.

Intersectable::IntersectionClass Intersectable::Intersects(AABox const & aabox, Frustum const & frustum)
{
    // from Moller, Thomas. Realtime Rendering, 2nd Ed., pp. 612-3
    //
    // The box intersects the frustum if it is not in front of any of the planes of the frustum. The box is enclosed by the frustum
    // if none of its vertexes is in front of any of the planes
    // of the frustum.

    bool intersectsAnyPlane = false;

    for (int i = 0; i < Frustum::NUM_SIDES; i++)
    {
        IntersectionClass ic = Intersects(HalfSpace(frustum.m_Sides[i]), aabox);
        if (ic == NO_INTERSECTION)
            return NO_INTERSECTION;
        if (ic == INTERSECTS)
            intersectsAnyPlane = true;
    }

    // Since it is not completely outside the frustum, if it intersects any plane then it intersects the frustum.
    // Otherwise it is completely inside.

    if (intersectsAnyPlane)
        return INTERSECTS;
    else
        return ENCLOSED_BY;
}

//! @param	a		The oriented box to test.
//! @param	b		The oriented box to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Box const & a, Box const & b)
{
    return NO_INTERSECTION;
}

//! @param	box			The oriented box to test.
//! @param	frustum		The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Box const & box, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a		The frustum to test.
//! @param	b		The frustum to test.
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Frustum const & a, Frustum const & b)
{
    return NO_INTERSECTION;
}

//! @param	point		point to test
//! @param	halfspace	halfspace to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Point const & point, HalfSpace const & halfspace)
{
    if (halfspace.m_Plane.DirectedDistance(point) <= 0.0f)
        return INTERSECTS;
    else
        return NO_INTERSECTION;
}

//! @param	line		line to test
//! @param	halfspace	halfspace to test
//!
//! @return		Returns NO_INTERSECTION or INTERSECTS.

Intersectable::IntersectionClass Intersectable::Intersects(Line const & line, HalfSpace const & halfspace)
{
    if (MyMath::IsCloseToZero(Dot(line.m_M, halfspace.m_Plane.m_N)))
        return Intersects(Point(line.m_B), halfspace);
    else
        return INTERSECTS;
}

//! @param	ray			ray to test
//! @param	halfspace	halfspace to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Ray const & ray, HalfSpace const & halfspace)
{
    return NO_INTERSECTION;
}

//! @param	segment		line segment to test
//! @param	halfspace	halfspace to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Segment const & segment, HalfSpace const & halfspace)
{
    return NO_INTERSECTION;
}

//! @param	plane	plane to test
//! @param	halfspace	halfspace to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(Plane const & plane, HalfSpace const & halfspace)
{
    return NO_INTERSECTION;
}

//! @param	a	halfspace to test
//! @param	b	halfspace to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & a, HalfSpace const & b)
{
    return NO_INTERSECTION;
}

//! @param	halfspace	halfspace to test
//! @param	poly		poly to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & halfspace, Poly const & poly)
{
    return NO_INTERSECTION;
}

//! @param	halfspace	halfspace to test
//! @param	sphere		sphere to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & halfspace, Sphere const & sphere)
{
    return NO_INTERSECTION;
}

//! @param	halfspace	halfspace to test
//! @param	cone		cone to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & halfspace, Cone const & cone)
{
    return NO_INTERSECTION;
}

//! @param	halfspace	halfspace to test
//! @param	aabox		AA box to test
//!
//! @return		Returns NO_INTERSECTION, INTERSECTS or ENCLOSES.

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & halfspace, AABox const & aabox)
{
    // from Moller, Thomas. Realtime Rendering, 2nd Ed., pp. 586-8
    //
    // The box intersects the plane if at least one of the vertexes of the box is not on the same side as the
    // one of the others. An optimization is to test only two vertexes along the diagonal most closely aligned
    // with the plane's normal.

    Point v0;
    Point v1;

    // Find the diagonal of the box (with endpoints v0 and v1) most closely aligned with the plane's normal

    if (halfspace.m_Plane.m_N.m_X >= 0.0f)
    {
        v0.m_X = aabox.m_Position.m_X;
        v1.m_X = aabox.m_Position.m_X + aabox.m_Scale.m_X;
    }
    else
    {
        v0.m_X = aabox.m_Position.m_X + aabox.m_Scale.m_X;
        v1.m_X = aabox.m_Position.m_X;
    }

    if (halfspace.m_Plane.m_N.m_Y >= 0.0f)
    {
        v0.m_Y = aabox.m_Position.m_Y;
        v1.m_Y = aabox.m_Position.m_Y + aabox.m_Scale.m_Y;
    }
    else
    {
        v0.m_Y = aabox.m_Position.m_Y + aabox.m_Scale.m_Y;
        v1.m_Y = aabox.m_Position.m_Y;
    }

    if (halfspace.m_Plane.m_N.m_Z >= 0.0f)
    {
        v0.m_Z = aabox.m_Position.m_Z;
        v1.m_Z = aabox.m_Position.m_Z + aabox.m_Scale.m_Z;
    }
    else
    {
        v0.m_Z = aabox.m_Position.m_Z + aabox.m_Scale.m_Z;
        v1.m_Z = aabox.m_Position.m_Z;
    }

    // If v0 is in front of the plane then the box is outside the half-space. If v1 is behind the plane then the
    // box is enclosed by the half-space. Otherwise, the box intersects the plane. Other cases do not need to be
    // considered because in the direction of the normal v1 is always greater than v0.

    if (halfspace.m_Plane.DirectedDistance(v0) > 0.0f)
        return NO_INTERSECTION;
    else if (halfspace.m_Plane.DirectedDistance(v1) < 0.0f)
        return ENCLOSES;
    else
        return INTERSECTS;
}

//! @param	halfspace	halfspace to test
//! @param	box			oriented box to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & halfspace, Box const & box)
{
    return NO_INTERSECTION;
}

//! @param	halfspace	halfspace to test
//! @param	frustum		frustum to test
//!
//! @todo	Not implemented

Intersectable::IntersectionClass Intersectable::Intersects(HalfSpace const & halfspace, Frustum const & frustum)
{
    return NO_INTERSECTION;
}

//! @param	a		The line to test.
//! @param	b		The line to test.
//! @param	ps		The place to store the parameter for line @a a where the intersection occurs.
//! @param	pt		The place to store the parameter for line @a b where the intersection occurs.
//!
//! @return			Number of intersections

int Intersectable::Intersection(Line const & a, Line const & b, float * ps, float * pt)
{
    Vector3 const n  = Cross(a.m_M, b.m_M);
    Vector3 const ab = b.m_B - a.m_B;

    // If the lines are parallel, then there are either 0 or infinite intersections ...

    if (MyMath::IsCloseToZero(n.Length2(), 2. * MyMath::DEFAULT_FLOAT_TOLERANCE))
    {
        float const d = Dot(ab, a.m_M);

        if (MyMath::IsRelativelyCloseTo(ab.Length2(), d * d, 2. * MyMath::DEFAULT_FLOAT_TOLERANCE))
            return std::numeric_limits<int>::max(); // Co-linear, return infinity
        else
            return 0;   // No intersection, return 0
    }

    // ... they are not parallel but if the distance between them is > 0 ...

    else if (!MyMath::IsCloseToZero(Dot(n, ab)))
    {
        return 0;   // No intersection, return 0
    }

    // ... otherwise, they intersect at a single point ...

    else
    {
        // Source: http://www.flipcode.com/geometry/gprimer2_issue02.shtml

        // Use the minor with largest determinant to maintain precision and prevent divide-by-0

        if (fabs(n.m_Z) > fabs(n.m_X)  &&  fabs(n.m_Z) > fabs(n.m_Y))
        {
            *ps =   (ab.m_X * b.m_M.m_Y - ab.m_Y * b.m_M.m_X) / n.m_Z;
            *pt = -(ab.m_X * a.m_M.m_Y - ab.m_Y * a.m_M.m_X) / n.m_Z;
        }
        else if (fabs(n.m_X) > fabs(n.m_Y))
        {
            *ps =   (ab.m_Y * b.m_M.m_Z - ab.m_Z * b.m_M.m_Y) / n.m_X;
            *pt = -(ab.m_Y * a.m_M.m_Z - ab.m_Z * a.m_M.m_Y) / n.m_X;
        }
        else
        {
            *ps =   (ab.m_Z * b.m_M.m_X - ab.m_X * b.m_M.m_Z) / n.m_Y;
            *pt = -(ab.m_Z * a.m_M.m_X - ab.m_X * a.m_M.m_Z) / n.m_Y;
        }

        return 1;   // 1 intersection, return 1
    }
}

//! @param	a		The line to test.
//! @param	b		The line to test.
//! @param	pi		The place to store the point of the intersection
//!
//! @return			The number of intersections.

int Intersectable::Intersection(Line const & a, Line const & b, Point * pi)
{
    float     t, u;
    int const n = Intersection(a, b, &t, &u);

    if (n == 1)
        *pi = a.m_M * t + a.m_B;

    return n;
}

//! @param	a		The line segment to test.
//! @param	b		The line segment to test.
//! @param	pi		The place to store the point of the intersection (if the intersection is a point)
//!
//! @return			The number of intersections.

int Intersectable::Intersection(Segment const & a, Segment const & b, Point * pi)
{
    float     t, u;
    int const n = Intersection(Line(a.m_M, a.m_B), Line(b.m_M, b.m_B), &t, &u);

    if (n == 1)
    {
        t *= a.m_M.ILength();
        u *= b.m_M.ILength();

        if (t < 0.f || t > 1.f || u < 0.f || u > 1.f)
            return 0;

        *pi = a.m_M * t + a.m_B;
    }

    return n;
}

//! @param	line		The line to test.
//! @param	plane		The plane to test.
//! @param	pt			Where to store the line's value of t at the intersection.
//!
//! @return				Number of intersections

int Intersectable::Intersection(Line const & line, Plane const & plane, float * pt)
{
    float const dot      = Dot(line.m_M, plane.m_N);
    float const distance = Distance(line.m_B, plane);

    // If the line and the plane are parallel then there are 0 or > 1 intersections

    if (MyMath::IsCloseToZero(dot))
    {
        if (MyMath::IsCloseToZero(distance))
            return std::numeric_limits<int>::max(); // Line is co-planar
        else
            return 0;   // Line does not intersect
    }

    *pt = -distance / dot;

    return 1;       // 1 intersection
}

//! @param	line	The line to test.
//! @param	plane	The plane to test.
//! @param	pi		The place to store the point of the intersection (if the intersection is a point)
//!
//! @return			Number of intersections

int Intersectable::Intersection(Line const & line, Plane const & plane, Point * pi)
{
    float     t;
    int const n = Intersection(line, plane, &t);

    if (n == 1)
        *pi = line.m_M * t + line.m_B;

    return n;
}

//! @param	a		The plane to test.
//! @param	b		The plane to test.
//! @param	pi		The place to store the intersection (if the intersection is a line)
//!
//! @return			Number of intersections

int Intersectable::Intersection(Plane const & a, Plane const & b, Line * pi)
{
    float const n1n2 = Dot(a.m_N, b.m_N);

    // If the Cross product of the normals is close to 0, the planes are parallel and possibly coincident

    if (MyMath::IsCloseTo(fabsf(n1n2), 1.))
    {
        // The planes are parallel, if the D values are the same, the planes are coincident, otherwise the do
        // not intersect

        if (MyMath::IsRelativelyCloseTo(a.m_D, b.m_D))
            return std::numeric_limits<int>::max();
        else
            return 0;
    }
    else
    {
        // p = ( c1 * N1 + c2 * N2 ) + u * ( N1 ^ N2 )
        float const n1n1 = Dot(a.m_N, a.m_N);
        float const n2n2 = Dot(b.m_N, b.m_N);
        float const d    = n1n1 * n2n2 - n1n2 * n1n2;
        float const c1   = (b.m_D * n1n2 - a.m_D * n2n2) / d;
        float const c2   = (a.m_D * n1n2 - b.m_D * n1n1) / d;

        pi->m_B = a.m_N * c1 + b.m_N * c2;
        pi->m_M = Cross(a.m_N, b.m_N);

        return 1;
    }
}

//! @param	a		The point to test.
//! @param	b		The point to test.
//!
//! Returns the distance between the points.

float Distance(Point const & a, Point const & b)
{
    return (a - b).Length();
}

//! @param	point		The point to test.
//! @param	line		The line to test.
//!
//! Returns the distance between the point and the line.

float Distance(Point const & point, Line const & line)
{
    // Distance in n-space is
    //
    //		|| (P - B) - ((P - B) dot M)M ||
    //
    // but in 3D/2D, it is also
    //
    //		|| M cross (P - B) ||
    //
    // which is slightly faster

    return Cross(point - line.m_B, line.m_M).Length();
}

//! @param	point		The point to test.
//! @param	ray			The ray to test.
//!
//! Returns the distance between the point and the ray.

float Distance(Point const & point, Ray const & ray)
{
    float const t = Dot((point - ray.m_B), ray.m_M);

    if (t <= 0.f)
        return Distance(point, ray.m_B);
    else
        return Distance(point, ray.m_B + ray.m_M * t);
}

//! @param	point		The point to test.
//! @param	segment		The line segment to test.
//!
//! Returns the distance between the point and the line segment.

float Distance(Point const & point, Segment const & segment)
{
    assert(!MyMath::IsCloseToZero(segment.m_M.Length2()));

    float const t = Dot((point - segment.m_B), segment.m_M) / segment.m_M.Length2();

    if (t <= 0.f)
        return Distance(point, segment.m_B);
    else if (t < 1.f)
        return Distance(point, segment.m_B + segment.m_M * t);
    else
        return Distance(point, segment.m_B + segment.m_M);
}

//! @param	point		The point to test.
//! @param	plane		The plane to test.
//!
//! Returns the distance between the point and the plane.

float Distance(Point const & point, Plane const & plane)
{
    return fabsf(Dot(plane.m_N, point) + plane.m_D);
}

//! @param	a		The line to test.
//! @param	b			The line to test.
//!
//! Returns the distance between the lines.

float Distance(Line const & a, Line const & b)
{
    // The distance between two lines is abs( ( a.m_M cross b.m_M ) dot ( a.m_B - b.m_B ) ) assuming the lines
    // are not parallel. If the lines are parallel, the distance is the distance from the line to any point
    // on the other line.

    Vector3 const cross = Cross(a.m_M, b.m_M);

    if (!MyMath::IsCloseToZero(cross.Length2(), 2. * MyMath::DEFAULT_FLOAT_TOLERANCE))
        return fabsf(Dot(cross, (a.m_B - b.m_B)));
    else
        return Distance(a.m_B, b);
}
