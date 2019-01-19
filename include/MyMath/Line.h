/** @file *//********************************************************************************************************

                                                        Line.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Line.h#15 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#include "Intersectable.h"

#include "MyMath.h"
#include "Vector3.h"

class Segment;
class Ray;

//! A line that can detect and compute intersections with other intersectables.
//
//! @ingroup Geometry
//!

class Line : public Intersectable
{
public:

    //! Constructor
    Line() {}

    //! Constructor
    Line(Vector3 const & m, Vector3 const & b);     // L = M * t + B

    //! Conversion
    explicit Line(Segment const & segment);

    //! Conversion
    explicit Line(Ray const & ray);

    //! Destructor
    virtual ~Line() {}

    //! @name Overrides Intersectable
    //@{
    virtual IntersectionClass IntersectedBy(Intersectable const * pI) const { return pI->Intersects(*this);                       }
    virtual IntersectionClass Intersects(Point const & point) const         { return Intersectable::Intersects(*this, point);     }
    virtual IntersectionClass Intersects(Line const & line) const           { return Intersectable::Intersects(*this, line);      }
    virtual IntersectionClass Intersects(Ray const & ray) const             { return Intersectable::Intersects(*this, ray);       }
    virtual IntersectionClass Intersects(Segment const & segment) const     { return Intersectable::Intersects(*this, segment);   }
    virtual IntersectionClass Intersects(Plane const & plane) const         { return Intersectable::Intersects(*this, plane);     }
    virtual IntersectionClass Intersects(HalfSpace const & halfspace) const { return Intersectable::Intersects(*this, halfspace); }
    virtual IntersectionClass Intersects(Poly const & poly) const           { return Intersectable::Intersects(*this, poly);      }
    virtual IntersectionClass Intersects(Sphere const & sphere) const       { return Intersectable::Intersects(*this, sphere);    }
    virtual IntersectionClass Intersects(Cone const & cone) const           { return Intersectable::Intersects(*this, cone);      }
    virtual IntersectionClass Intersects(AABox const & aabox) const         { return Intersectable::Intersects(*this, aabox);     }
    virtual IntersectionClass Intersects(Box const & box) const             { return Intersectable::Intersects(*this, box);       }
    virtual IntersectionClass Intersects(Frustum const & frustum) const     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    //! Returns the location of a point projected onto the line (also the closest point on the line to the point).
    Point Project(Point const & point) const;

    // Line equation: L = m_M * t + m_B

    Vector3 m_M;    //!< Direction (length is always 1)
    Vector3 m_B;    //!< Location of a point on the line
};

//! A ray that can detect and compute intersections with other intersectables.
//
//! @ingroup Geometry
//!

class Ray : public Intersectable
{
public:

    //! Constructor
    Ray() {}

    //! Constructor
    Ray(Vector3 const & m, Vector3 const & b);      // L = M * t + B, t >= 0

    //! Destructor
    virtual ~Ray() {}

    //! @name Overrides Intersectable
    //@{
    virtual IntersectionClass IntersectedBy(Intersectable const * pI) const { return pI->Intersects(*this);                       }
    virtual IntersectionClass Intersects(Point const & point) const         { return Intersectable::Intersects(*this, point);     }
    virtual IntersectionClass Intersects(Line const & line) const           { return Intersectable::Intersects(*this, line);      }
    virtual IntersectionClass Intersects(Ray const & ray) const             { return Intersectable::Intersects(*this, ray);       }
    virtual IntersectionClass Intersects(Segment const & segment) const     { return Intersectable::Intersects(*this, segment);   }
    virtual IntersectionClass Intersects(HalfSpace const & halfspace) const { return Intersectable::Intersects(*this, halfspace); }
    virtual IntersectionClass Intersects(Plane const & plane) const         { return Intersectable::Intersects(*this, plane);     }
    virtual IntersectionClass Intersects(Poly const & poly) const           { return Intersectable::Intersects(*this, poly);      }
    virtual IntersectionClass Intersects(Sphere const & sphere) const       { return Intersectable::Intersects(*this, sphere);    }
    virtual IntersectionClass Intersects(Cone const & cone) const           { return Intersectable::Intersects(*this, cone);      }
    virtual IntersectionClass Intersects(AABox const & aabox) const         { return Intersectable::Intersects(*this, aabox);     }
    virtual IntersectionClass Intersects(Box const & box) const             { return Intersectable::Intersects(*this, box);       }
    virtual IntersectionClass Intersects(Frustum const & frustum) const     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    //! Returns the location of a point projected onto the line which goes through the ray.
    Point Project(Point const & point) const;

    // Ray equation: L = m_M * t + m_B, t >= 0

    Vector3 m_M;    //!< Direction (length is always 1)
    Vector3 m_B;    //!< Location of a point on the line
};

//! A line segment that can detect and compute intersections with other intersectables.
//
//! @ingroup Geometry
//!

class Segment : public Intersectable
{
public:

    //! Constructor
    Segment() {}

    //! Constructor
    Segment(Vector3 const & p0, Vector3 const & p1);

    //! Constructor
    Segment(Vector3 const & m, Vector3 const & b, float length);    // L = M * t + B, 0 <= t <= length

    //! Destructor
    virtual ~Segment() {}

    //! @name Overrides Intersectable
    //@{
    virtual IntersectionClass IntersectedBy(Intersectable const * pI) const { return pI->Intersects(*this);                       }
    virtual IntersectionClass Intersects(Point const & point) const         { return Intersectable::Intersects(*this, point);     }
    virtual IntersectionClass Intersects(Line const & line) const           { return Intersectable::Intersects(*this, line);      }
    virtual IntersectionClass Intersects(Ray const & ray) const             { return Intersectable::Intersects(*this, ray);       }
    virtual IntersectionClass Intersects(Segment const & segment) const     { return Intersectable::Intersects(*this, segment);   }
    virtual IntersectionClass Intersects(Plane const & plane) const         { return Intersectable::Intersects(*this, plane);     }
    virtual IntersectionClass Intersects(HalfSpace const & halfspace) const { return Intersectable::Intersects(*this, halfspace); }
    virtual IntersectionClass Intersects(Poly const & poly) const           { return Intersectable::Intersects(*this, poly);      }
    virtual IntersectionClass Intersects(Sphere const & sphere) const       { return Intersectable::Intersects(*this, sphere);    }
    virtual IntersectionClass Intersects(Cone const & cone) const           { return Intersectable::Intersects(*this, cone);      }
    virtual IntersectionClass Intersects(AABox const & aabox) const         { return Intersectable::Intersects(*this, aabox);     }
    virtual IntersectionClass Intersects(Box const & box) const             { return Intersectable::Intersects(*this, box);       }
    virtual IntersectionClass Intersects(Frustum const & frustum) const     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    //! Returns the location of a point projected onto the line which goes through the segment.
    Point Project(Point const & point) const;

    // Segment equation: L = m_M * t + m_B, 0 <= t <= 1

    Vector3 m_M;    //!< Direction (length of m_M is the length of the segment)
    Vector3 m_B;    //!< Location of endpoint at t = 0
};

// Inline functions

#include "Misc/Assert.h"

//! @param	m	Direction of the line. The vector must be normalized.
//! @param	b	A point on the line

inline Line::Line(Vector3 const & m, Vector3 const & b)
    : m_M(m)
    , m_B(b)
{
    assert(m.IsNormalized());
}

//! This function constructs a line that is colinear with the ray.
//!
//! @param ray	A ray

inline Line::Line(Ray const & ray)
    : m_M(ray.m_M)
    , m_B(ray.m_B)
{
}

//! This function constructs a line that is colinear with the segment.
//!
//! @param segment	A line segment

inline Line::Line(Segment const & segment)
    : m_M(segment.m_M)
    , m_B(segment.m_B)
{
    assert(!MyMath::IsCloseToZero(m_M.Length()));
    m_M.Normalize();
}

//! @param	m	Direction of the ray. The vector must be normalized.
//! @param	b	The endpoint of the ray

inline Ray::Ray(Vector3 const & m, Vector3 const & b)
    : m_M(m)
    , m_B(b)
{
    assert(m.IsNormalized());
}

//! This function constructs a line segment between two points.
//!
//! @param	p0,p1	Endpoints

inline Segment::Segment(Vector3 const & p0, Vector3 const & p1)
{
    m_M = p1 - p0;
    m_B = p0;
}

//! @param	m		Direction of the line segment. The vector must be normalized.
//! @param	b		The endpoint of the line segment when t == 0
//! @param	length	The length of the segment

inline Segment::Segment(Vector3 const & m, Vector3 const & b, float length)
{
    assert(m.IsNormalized());
    assert(!MyMath::IsCloseToZero(length));

    m_M = m * length;
    m_B = b;
}
