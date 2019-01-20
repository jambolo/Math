#pragma once

#if !defined(MYMATH_POINT_H)
#define MYMATH_POINT_H

#include "Intersectable.h"
#include "Vector3.h"

//! A point that can detect and compute intersections with other intersectable objects.
//
//! @ingroup Geometry
//!

class Point : public Intersectable
{
public:

    //! Constructor
    Point() = default;

    //! Constructor
    Point(float x, float y, float z) : value_(x, y, z) {}

    //! Constructor
    Point(float const v[3]) : value_(v) {}

    //! Conversion
    Point(Vector3 const & v) : value_(v) {}

    //! @name Overrides Intersectable
    //@{
    virtual Result IntersectedBy(Intersectable const * pI) const override { return pI->Intersects(*this);                       }
    virtual Result Intersects(Point const & point) const override         { return Intersectable::Intersects(*this, point);     }
    virtual Result Intersects(Line const & line) const override           { return Intersectable::Intersects(*this, line);      }
    virtual Result Intersects(Ray const & ray) const override             { return Intersectable::Intersects(*this, ray);       }
    virtual Result Intersects(Segment const & segment) const override     { return Intersectable::Intersects(*this, segment);   }
    virtual Result Intersects(Plane const & plane) const override         { return Intersectable::Intersects(*this, plane);     }
    virtual Result Intersects(HalfSpace const & halfspace) const override { return Intersectable::Intersects(*this, halfspace); }
    virtual Result Intersects(Poly const & poly) const override           { return Intersectable::Intersects(*this, poly);      }
    virtual Result Intersects(Sphere const & sphere) const override       { return Intersectable::Intersects(*this, sphere);    }
    virtual Result Intersects(Cone const & cone) const override           { return Intersectable::Intersects(*this, cone);      }
    virtual Result Intersects(AABox const & aabox) const override         { return Intersectable::Intersects(*this, aabox);     }
    virtual Result Intersects(Box const & box) const override             { return Intersectable::Intersects(*this, box);       }
    virtual Result Intersects(Frustum const & frustum) const override     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    Vector3 value_;
};

#endif // !defined(MYMATH_POINT_H)
