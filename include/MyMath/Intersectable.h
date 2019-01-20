#pragma once

#if !defined(MYMATH_INTERSECTABLE_H)
#define MYMATH_INTERSECTABLE_H

#include "Misc/Assert.h"

class Point;
class Line;
class Ray;
class Segment;
class Plane;
class HalfSpace;
class Poly;
class Sphere;
class Cone;
class AABox;
class Box;
class Frustum;
class Vector3;

//! A class that can detect and compute intersections with other instances
//
//! @ingroup	Geometry
//!
//! The objects that are tested can be divided into two groups:
//!
//!		- objects with volume
//!			- HalfSpace
//!			- Sphere
//!			- Cone
//!			- AABox
//!			- Box
//!			- Frustum
//!
//!		- objects without volume
//!			- Point
//!			- Line
//!			- Ray
//!			- Segment
//!			- Plane
//!			- Poly
//!
//! The results of an intersection test depend on the types of the objects being tested:
//!
//!		- two objects without volume
//!			- INTERSECTS is returned if the nearest distance between the two objects is less than the default
//!			  float tolerance value.
//!			- NO_INTERSECTION is returned otherwise.
//!		- an object with volume vs. an object without volume
//!			- INTERSECTS is returned if the object without volume intersects the object with volume.
//!			- NO_INTERSECTION is returned otherwise.
//!		- two objects with volume
//!			- ENCLOSES is returned if the first volume completely encloses the second.
//!			- ENCLOSED_BY is returned if the first volume is completely enclosed by the second.
//!			- INTERSECTS is returned if the volumes intersect but neither encloses the other.
//!			- NO_INTERSECTION is return otherwise.
//!

class Intersectable
{
public:

    Intersectable()          = default;
    virtual ~Intersectable() = default;

    //! Values that describes an intersection
    enum Result
    {
        NO_INTERSECTION,    //!< The two objects do not intersect
        INTERSECTS,         //!< The two objects intersect
        ENCLOSES,           //!< The first object (intersector) completely encloses the second object (intersectee).
        ENCLOSED_BY         //!< The second object (intersectee) completely encloses the first object (intersector).
    };

    //! Returns the class of intersection between the other object and this object.
    virtual Result IntersectedBy(Intersectable const * pI) const = 0;

    //! Returns the class of intersection between this object and the point.
    virtual Result Intersects(Point const & point) const = 0;

    //! Returns the class of intersection between this object and the line.
    virtual Result Intersects(Line const & line) const = 0;

    //! Returns the class of intersection between this object and the ray.
    virtual Result Intersects(Ray const & ray) const = 0;

    //! Returns the class of intersection between this object and the segment.
    virtual Result Intersects(Segment const & segment) const = 0;

    //! Returns the class of intersection between this object and the plane.
    virtual Result Intersects(Plane const & plane) const = 0;

    //! Returns the class of intersection between this object and the halfspace.
    virtual Result Intersects(HalfSpace const & halfspace) const = 0;

    //! Returns the class of intersection between this object and the poly.
    virtual Result Intersects(Poly const & poly) const = 0;

    //! Returns the class of intersection between this object and the sphere.
    virtual Result Intersects(Sphere const & sphere) const = 0;

    //! Returns the class of intersection between this object and the cone.
    virtual Result Intersects(Cone const & cone) const = 0;

    //! Returns the class of intersection between this object and the AA box.
    virtual Result Intersects(AABox const & aabox) const = 0;

    //! Returns the class of intersection between this object and the box.
    virtual Result Intersects(Box const & box) const = 0;

    //! Returns the class of intersection between this object and the frustum.
    virtual Result Intersects(Frustum const & frustum) const = 0;

protected:

    //! @name  Intersection with a Point Determination
    //@{

    //! Returns the class of intersection between the points.
    static Result Intersects(Point const & a, Point const & b);

    //! Returns the class of intersection between the point and the line.
    static Result Intersects(Point const & point, Line const & line);

    //! Returns the class of intersection between the point and the ray.
    static Result Intersects(Point const & point, Ray const & ray);

    //! Returns the class of intersection between the point and the segment.
    static Result Intersects(Point const & point, Segment const & segment);

    //! Returns the class of intersection between the point and the plane.
    static Result Intersects(Point const & point, Plane const & plane);

    //! Returns the class of intersection between the point and the half-space.
    static Result Intersects(Point const & point, HalfSpace const & halfspace);

    //! Returns the class of intersection between the point and the poly.
    static Result Intersects(Point const & point, Poly const & poly);

    //! Returns the class of intersection between the point and the sphere.
    static Result Intersects(Point const & point, Sphere const & sphere);

    //! Returns the class of intersection between the point and the sphere.
    static Result Intersects(Point const & point, Cone const & sphere);

    //! Returns the class of intersection between the point and the aabox.
    static Result Intersects(Point const & point, AABox const & aabox);

    //! Returns the class of intersection between the point and the box.
    static Result Intersects(Point const & point, Box const & box);

    //! Returns the class of intersection between the point and the frustum.
    static Result Intersects(Point const & point, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Line Determination
    //@{

    //! Returns the class of intersection between the line and the point.
    static Result Intersects(Line const & line, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, line));
    }

    //! Returns the class of intersection between the lines.
    static Result Intersects(Line const & a, Line const & b);

    //! Returns the class of intersection between the line and the ray.
    static Result Intersects(Line const & line, Ray const & ray);

    //! Returns the class of intersection between the line and the segment.
    static Result Intersects(Line const & line, Segment const & segment);

    //! Returns the class of intersection between the line and the plane.
    static Result Intersects(Line const & line, Plane const & plane);

    //! Returns the class of intersection between the line and the half-space.
    static Result Intersects(Line const & line, HalfSpace const & halfspace);

    //! Returns the class of intersection between the line and the poly.
    static Result Intersects(Line const & line, Poly const & poly);

    //! Returns the class of intersection between the line and the sphere.
    static Result Intersects(Line const & line, Sphere const & sphere);

    //! Returns the class of intersection between the line and the cone.
    static Result Intersects(Line const & line, Cone const & cone);

    //! Returns the class of intersection between the line and the aabox.
    static Result Intersects(Line const & line, AABox const & aabox);

    //! Returns the class of intersection between the line and the box.
    static Result Intersects(Line const & line, Box const & box);

    //! Returns the class of intersection between the line and the frustum.
    static Result Intersects(Line const & line, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Ray Determination
    //@{

    //! Returns the class of intersection between the ray and the point.
    static Result Intersects(Ray const & ray, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, ray));
    }

    //! Returns the class of intersection between the ray and the line.
    static Result Intersects(Ray const & ray, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, ray));
    }

    //! Returns the class of intersection between the rays.
    static Result Intersects(Ray const & a, Ray const & b);

    //! Returns the class of intersection between the ray and the segment.
    static Result Intersects(Ray const & ray, Segment const & segment);

    //! Returns the class of intersection between the ray and the plane.
    static Result Intersects(Ray const & ray, Plane const & plane);

    //! Returns the class of intersection between the ray and the half-space.
    static Result Intersects(Ray const & ray, HalfSpace const & halfspace);

    //! Returns the class of intersection between the ray and the poly.
    static Result Intersects(Ray const & ray, Poly const & poly);

    //! Returns the class of intersection between the ray and the sphere.
    static Result Intersects(Ray const & ray, Sphere const & sphere);

    //! Returns the class of intersection between the ray and the cone.
    static Result Intersects(Ray const & ray, Cone const & cone);

    //! Returns the class of intersection between the ray and the aabox.
    static Result Intersects(Ray const & ray, AABox const & aabox);

    //! Returns the class of intersection between the ray and the box.
    static Result Intersects(Ray const & ray, Box const & box);

    //! Returns the class of intersection between the ray and the frustum.
    static Result Intersects(Ray const & ray, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Segment Determination
    //@{

    //! Returns the class of intersection between the segment and the point.
    static Result Intersects(Segment const & segment, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, segment));
    }

    //! Returns the class of intersection between the segment and the line.
    static Result Intersects(Segment const & segment, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, segment));
    }

    //! Returns the class of intersection between the segment and the ray.
    static Result Intersects(Segment const & segment, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, segment));
    }

    //! Returns the class of intersection between the segments.
    static Result Intersects(Segment const & a, Segment const & b);

    //! Returns the class of intersection between the segment and the plane.
    static Result Intersects(Segment const & segment, Plane const & plane);

    //! Returns the class of intersection between the segment and the half-space.
    static Result Intersects(Segment const & segment, HalfSpace const & halfspace);

    //! Returns the class of intersection between the segment and the poly.
    static Result Intersects(Segment const & segment, Poly const & poly);

    //! Returns the class of intersection between the segment and the sphere.
    static Result Intersects(Segment const & segment, Sphere const & sphere);

    //! Returns the class of intersection between the segment and the cone.
    static Result Intersects(Segment const & segment, Cone const & cone);

    //! Returns the class of intersection between the segment and the aabox.
    static Result Intersects(Segment const & segment, AABox const & aabox);

    //! Returns the class of intersection between the segment and the box.
    static Result Intersects(Segment const & segment, Box const & box);

    //! Returns the class of intersection between the segment and the frustum.
    static Result Intersects(Segment const & segment, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Plane Determination
    //@{

    //! Returns the class of intersection between the plane and the point.
    static Result Intersects(Plane const & plane, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, plane));
    }

    //! Returns the class of intersection between the plane and the line.
    static Result Intersects(Plane const & plane, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, plane));
    }

    //! Returns the class of intersection between the plane and the ray.
    static Result Intersects(Plane const & plane, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, plane));
    }

    //! Returns the class of intersection between the plane and the segment.
    static Result Intersects(Plane const & plane, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, plane));
    }

    //! Returns the class of intersection between the planes.
    static Result Intersects(Plane const & a, Plane const & b);

    //! Returns the class of intersection between the plane and the half-space.
    static Result Intersects(Plane const & plane, HalfSpace const & halfspace);

    //! Returns the class of intersection between the plane and the poly.
    static Result Intersects(Plane const & plane, Poly const & poly);

    //! Returns the class of intersection between the plane and the sphere.
    static Result Intersects(Plane const & plane, Sphere const & sphere);

    //! Returns the class of intersection between the plane and the cone.
    static Result Intersects(Plane const & plane, Cone const & cone);

    //! Returns the class of intersection between the plane and the aabox.
    static Result Intersects(Plane const & plane, AABox const & aabox);

    //! Returns the class of intersection between the plane and the box.
    static Result Intersects(Plane const & plane, Box const & box);

    //! Returns the class of intersection between the plane and the frustum.
    static Result Intersects(Plane const & plane, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Half-Space Determination
    //@{

    //! Returns the class of intersection between the halfspace and the point.
    static Result Intersects(HalfSpace const & halfspace, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, halfspace));
    }

    //! Returns the class of intersection between the halfspace and the line.
    static Result Intersects(HalfSpace const & halfspace, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, halfspace));
    }

    //! Returns the class of intersection between the halfspace and the ray.
    static Result Intersects(HalfSpace const & halfspace, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, halfspace));
    }

    //! Returns the class of intersection between the halfspace and the segment.
    static Result Intersects(HalfSpace const & halfspace, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, halfspace));
    }

    //! Returns the class of intersection between the halfspaces.
    static Result Intersects(HalfSpace const & halfspace, Plane const & plane)
    {
        return ReversedEnclosure(Intersects(plane, halfspace));
    }

    //! Returns the class of intersection between the half-spaces.
    static Result Intersects(HalfSpace const & a, HalfSpace const & b);

    //! Returns the class of intersection between the halfspace and the poly.
    static Result Intersects(HalfSpace const & halfspace, Poly const & poly);

    //! Returns the class of intersection between the halfspace and the sphere.
    static Result Intersects(HalfSpace const & halfspace, Sphere const & sphere);

    //! Returns the class of intersection between the halfspace and the cone.
    static Result Intersects(HalfSpace const & halfspace, Cone const & cone);

    //! Returns the class of intersection between the halfspace and the aabox.
    static Result Intersects(HalfSpace const & halfspace, AABox const & aabox);

    //! Returns the class of intersection between the halfspace and the box.
    static Result Intersects(HalfSpace const & halfspace, Box const & box);

    //! Returns the class of intersection between the halfspace and the frustum.
    static Result Intersects(HalfSpace const & halfspace, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Poly Determination
    //@{

    //! Returns the class of intersection between the poly and the point.
    static Result Intersects(Poly const & poly, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, poly));
    }

    //! Returns the class of intersection between the poly and the line.
    static Result Intersects(Poly const & poly, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, poly));
    }

    //! Returns the class of intersection between the poly and the ray.
    static Result Intersects(Poly const & poly, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, poly));
    }

    //! Returns the class of intersection between the poly and the segment.
    static Result Intersects(Poly const & poly, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, poly));
    }

    //! Returns the class of intersection between the poly and the plane.
    static Result Intersects(Poly const & poly, Plane const & plane) {
        return ReversedEnclosure(Intersects(plane, poly));
    }

    //! Returns the class of intersection between the poly and the half-space.
    static Result Intersects(Poly const & poly, HalfSpace const & halfspace)
    {
        return ReversedEnclosure(Intersects(halfspace, poly));
    }

    //! Returns the class of intersection between the polys.
    static Result Intersects(Poly const & a, Poly const & b);

    //! Returns the class of intersection between the poly and the sphere.
    static Result Intersects(Poly const & poly, Sphere const & sphere);

    //! Returns the class of intersection between the poly and the cone.
    static Result Intersects(Poly const & poly, Cone const & cone);

    //! Returns the class of intersection between the poly and the aabox.
    static Result Intersects(Poly const & poly, AABox const & aabox);

    //! Returns the class of intersection between the poly and the box.
    static Result Intersects(Poly const & poly, Box const & box);

    //! Returns the class of intersection between the poly and the frustum.
    static Result Intersects(Poly const & poly, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Sphere Determination
    //@{

    //! Returns the class of intersection between the sphere and the point.
    static Result Intersects(Sphere const & sphere, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, sphere));
    }

    //! Returns the class of intersection between the sphere and the line.
    static Result Intersects(Sphere const & sphere, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, sphere));
    }

    //! Returns the class of intersection between the sphere and the ray.
    static Result Intersects(Sphere const & sphere, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, sphere));
    }

    //! Returns the class of intersection between the sphere and the segment.
    static Result Intersects(Sphere const & sphere, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, sphere));
    }

    //! Returns the class of intersection between the sphere and the plane.
    static Result Intersects(Sphere const & sphere, Plane const & plane)
    {
        return ReversedEnclosure(Intersects(plane, sphere));
    }

    //! Returns the class of intersection between the sphere and the half-space.
    static Result Intersects(Sphere const & sphere, HalfSpace const & halfspace)
    {
        return ReversedEnclosure(Intersects(halfspace, sphere));
    }

    //! Returns the class of intersection between the sphere and the poly.
    static Result Intersects(Sphere const & sphere, Poly const & poly)
    {
        return ReversedEnclosure(Intersects(poly, sphere));
    }

    //! Returns the class of intersection between the spheres.
    static Result Intersects(Sphere const & a, Sphere const & b);

    //! Returns the class of intersection between the sphere and the cone.
    static Result Intersects(Sphere const & a, Cone const & cone);

    //! Returns the class of intersection between the sphere and the aabox.
    static Result Intersects(Sphere const & sphere, AABox const & aabox);

    //! Returns the class of intersection between the sphere and the box.
    static Result Intersects(Sphere const & sphere, Box const & box);

    //! Returns the class of intersection between the sphere and the frustum.
    static Result Intersects(Sphere const & sphere, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Cone Determination
    //@{

    //! Returns the class of intersection between the cone and the point.
    static Result Intersects(Cone const & cone, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, cone));
    }

    //! Returns the class of intersection between the cone and the line.
    static Result Intersects(Cone const & cone, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, cone));
    }

    //! Returns the class of intersection between the cone and the ray.
    static Result Intersects(Cone const & cone, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, cone));
    }

    //! Returns the class of intersection between the cone and the segment.
    static Result Intersects(Cone const & cone, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, cone));
    }

    //! Returns the class of intersection between the cone and the plane.
    static Result Intersects(Cone const & cone, Plane const & plane)
    {
        return ReversedEnclosure(Intersects(plane, cone));
    }

    //! Returns the class of intersection between the cone and the half-space.
    static Result Intersects(Cone const & cone, HalfSpace const & halfspace)
    {
        return ReversedEnclosure(Intersects(halfspace, cone));
    }

    //! Returns the class of intersection between the cone and the poly.
    static Result Intersects(Cone const & cone, Poly const & poly)
    {
        return ReversedEnclosure(Intersects(poly, cone));
    }

    //! Returns the class of intersection between the cone and the sphere.
    static Result Intersects(Cone const & cone, Sphere const & sphere)
    {
        return ReversedEnclosure(Intersects(sphere, cone));
    }

    //! Returns the class of intersection between the cones.
    static Result Intersects(Cone const & a, Cone const & b);

    //! Returns the class of intersection between the cone and the aabox.
    static Result Intersects(Cone const & cone, AABox const & aabox);

    //! Returns the class of intersection between the cone and the box.
    static Result Intersects(Cone const & cone, Box const & box);

    //! Returns the class of intersection between the cone and the frustum.
    static Result Intersects(Cone const & cone, Frustum const & frustum);

    //@}
    //! @name  Intersection with an AABox Determination
    //@{

    //! Returns the class of intersection between the AA box and the point.
    static Result Intersects(AABox const & aabox, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, aabox));
    }

    //! Returns the class of intersection between the AA box and the line.
    static Result Intersects(AABox const & aabox, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, aabox));
    }

    //! Returns the class of intersection between the AA box and the ray.
    static Result Intersects(AABox const & aabox, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, aabox));
    }

    //! Returns the class of intersection between the AA box and the segment.
    static Result Intersects(AABox const & aabox, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, aabox));
    }

    //! Returns the class of intersection between the AA box and the plane.
    static Result Intersects(AABox const & aabox, Plane const & plane)
    {
        return ReversedEnclosure(Intersects(plane, aabox));
    }

    //! Returns the class of intersection between the AA box and the half-space.
    static Result Intersects(AABox const & aabox, HalfSpace const & halfspace)
    {
        return ReversedEnclosure(Intersects(halfspace, aabox));
    }

    //! Returns the class of intersection between the AA box and the poly.
    static Result Intersects(AABox const & aabox, Poly const & poly)
    {
        return ReversedEnclosure(Intersects(poly, aabox));
    }

    //! Returns the class of intersection between the AA box and the sphere.
    static Result Intersects(AABox const & aabox, Sphere const & sphere)
    {
        return ReversedEnclosure(Intersects(sphere, aabox));
    }

    //! Returns the class of intersection between the AA box and the cone.
    static Result Intersects(AABox const & aabox, Cone const & cone)
    {
        return ReversedEnclosure(Intersects(cone, aabox));
    }

    //! Returns true if the AA boxes intersect.
    static Result Intersects(AABox const & a, AABox const & b);

    //! Returns the class of intersection between the AA box and the box.
    static Result Intersects(AABox const & aabox, Box const & box);

    //! Returns the class of intersection between the AA box and the frustum.
    static Result Intersects(AABox const & aabox, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Box Determination
    //@{

    //! Returns the class of intersection between the box and the point.
    static Result Intersects(Box const & box, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, box));
    }

    //! Returns the class of intersection between the box and the line.
    static Result Intersects(Box const & box, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, box));
    }

    //! Returns the class of intersection between the box and the ray.
    static Result Intersects(Box const & box, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, box));
    }

    //! Returns the class of intersection between the box and the segment.
    static Result Intersects(Box const & box, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, box));
    }

    //! Returns the class of intersection between the box and the plane.
    static Result Intersects(Box const & box, Plane const & plane)
    {
        return ReversedEnclosure(Intersects(plane, box));
    }

    //! Returns the class of intersection between the box and the half-space.
    static Result Intersects(Box const & box, HalfSpace const & halfspace)
    {
        return ReversedEnclosure(Intersects(halfspace, box));
    }

    //! Returns the class of intersection between the box and the poly.
    static Result Intersects(Box const & box, Poly const & poly)
    {
        return ReversedEnclosure(Intersects(poly, box));
    }

    //! Returns the class of intersection between the box and the sphere.
    static Result Intersects(Box const & box, Sphere const & sphere)
    {
        return ReversedEnclosure(Intersects(sphere, box));
    }

    //! Returns the class of intersection between the box and the cone.
    static Result Intersects(Box const & box, Cone const & cone)
    {
        return ReversedEnclosure(Intersects(cone, box));
    }

    //! Returns the class of intersection between the box and the aabox.
    static Result Intersects(Box const & box, AABox const & aabox)
    {
        return ReversedEnclosure(Intersects(aabox, box));
    }

    //! Returns the class of intersection between the boxes.
    static Result Intersects(Box const & a, Box const & b);

    //! Returns the class of intersection between the box and the frustum.
    static Result Intersects(Box const & box, Frustum const & frustum);

    //@}
    //! @name  Intersection with a Frustum Determination
    //@{

    //! Returns the class of intersection between the frustum and the point.
    static Result Intersects(Frustum const & frustum, Point const & point)
    {
        return ReversedEnclosure(Intersects(point, frustum));
    }

    //! Returns the class of intersection between the frustum and the line.
    static Result Intersects(Frustum const & frustum, Line const & line)
    {
        return ReversedEnclosure(Intersects(line, frustum));
    }

    //! Returns the class of intersection between the frustum and the ray.
    static Result Intersects(Frustum const & frustum, Ray const & ray)
    {
        return ReversedEnclosure(Intersects(ray, frustum));
    }

    //! Returns the class of intersection between the frustum and the segment.
    static Result Intersects(Frustum const & frustum, Segment const & segment)
    {
        return ReversedEnclosure(Intersects(segment, frustum));
    }

    //! Returns the class of intersection between the frustum and the plane.
    static Result Intersects(Frustum const & frustum, Plane const & plane)
    {
        return ReversedEnclosure(Intersects(plane, frustum));
    }

    //! Returns the class of intersection between the frustum and the half-space.
    static Result Intersects(Frustum const & frustum, HalfSpace const & halfspace)
    {
        return ReversedEnclosure(Intersects(halfspace, frustum));
    }

    //! Returns the class of intersection between the frustum and the poly.
    static Result Intersects(Frustum const & frustum, Poly const & poly)
    {
        return ReversedEnclosure(Intersects(poly, frustum));
    }

    //! Returns the class of intersection between the frustum and the sphere.
    static Result Intersects(Frustum const & frustum, Sphere const & sphere)
    {
        return ReversedEnclosure(Intersects(sphere, frustum));
    }

    //! Returns the class of intersection between the frustum and the cone.
    static Result Intersects(Frustum const & frustum, Cone const & cone)
    {
        return ReversedEnclosure(Intersects(cone, frustum));
    }

    //! Returns the class of intersection between the frustum and the aabox.
    static Result Intersects(Frustum const & frustum, AABox const & aabox)
    {
        return ReversedEnclosure(Intersects(aabox, frustum));
    }

    //! Returns the class of intersection between the frustum and the box.
    static Result Intersects(Frustum const & frustum, Box const & box)
    {
        return ReversedEnclosure(Intersects(box, frustum));
    }

    //! Returns the class of intersection between the frustums.
    static Result Intersects(Frustum const & a, Frustum const & b);

    //@}
    //! @name  Intersection Computation
    //@{

    //! Returns the intersection of two Lines.
    static int Intersection(Line const & a, Line const & b, float * pt, float * pu);

    //! Returns the intersection of two Lines.
    static int Intersection(Line const & a, Line const & b, Point * pi);

    //! Returns the intersection of two Segments.
    static int Intersection(Segment const & a, Segment const & b, Point * pi);

    //! Returns the intersection of a Line and a Plane.
    static int Intersection(Line const & line, Plane const & plane, float * pt);

    //! Returns the intersection of a Line and a Plane.
    static int Intersection(Line const & line, Plane const & plane, Point * pi);

    //! Returns the intersection of two Planes.
    static int Intersection(Plane const & a, Plane const & b, Line * pi);

    //@}

private:

    static Result ReversedEnclosure(Result c)
    {
        // This swaps ENCLOSES (2) and ENCLOSED_BY (3), but does nothing to NO_INTERSECTION (0)
        // and INTERSECTS (1).

        assert(((static_cast<int>(NO_INTERSECTION) & 2) == 0) && ((static_cast<int>(INTERSECTS) & 2) == 0));
        assert(((static_cast<int>(ENCLOSES) & 2) != 0) && ((static_cast<int>(ENCLOSED_BY) & 2) != 0));

        return static_cast<Result>(static_cast<int>(c) ^ (static_cast<int>(c) >> 1));
    }
};

//! @defgroup	Distance	Distance Computation
//! @ingroup Geometry
//@{

//! Returns the distance between two Points.
float Distance(Point const & a, Point const & b);

//! Returns the distance between a line and a point.
float Distance(Point const & point, Line const & line);

//! Returns the distance between a ray and a point.
float Distance(Point const & point, Ray const & ray);

//! Returns the distance between a line segment and a point.
float Distance(Point const & point, Segment const & segment);

//! Returns the distance between a point and a plane.
float Distance(Point const & point, Plane const & plane);

//! Returns the distance between a line and a point.
inline float Distance(Line const & line, Point const & point) { return Distance(point, line); }

//! Return the closest distance between two lines.
float Distance(Line const & a, Line const & b);

//! Returns the distance between a ray and a point.
inline float Distance(Ray const & ray, Point const & point) { return Distance(point, ray); }

//! Returns the distance between a line segment and a point.
inline float Distance(Segment const & segment, Point const & point) { return Distance(point, segment); }

//! Returns the distance between a point and a plane.
inline float Distance(Plane const & plane, Point const & point) { return Distance(point, plane); }

//@}

#endif // !defined(MYMATH_INTERSECTABLE_H)
