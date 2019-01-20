#pragma once

#if !defined(MYMATH_SPHERE_H)
#define MYMATH_SPHERE_H

#include "Intersectable.h"
#include "Vector3.h"

//! A sphere that can detect and compute intersections with other intersectable objects.
//
//! @ingroup Geometry
//!

class Sphere : public Intersectable
{
public:

    //! Constructor
    Sphere() = default;

    //! Constructor
    Sphere(Vector3 const & c, float r) : m_C(c)
        , m_R(r)   {}

    //! Destructor
    virtual ~Sphere() override = default;

    //! @name Overrides Intersectable
    //@{
    virtual Result IntersectedBy(Intersectable const * pI) const override { return pI->Intersects(*this);                       }
    virtual Result Intersects(Point const & point) const override         { return Intersectable::Intersects(*this, point);     }
    virtual Result Intersects(Line const & line) const override           { return Intersectable::Intersects(*this, line);      }
    virtual Result Intersects(Ray const & ray) const override             { return Intersectable::Intersects(*this, ray);       }
    virtual Result Intersects(Segment const & segment) const override     { return Intersectable::Intersects(*this, segment);   }
    virtual Result Intersects(Plane const & plane) const override         { return Intersectable::Intersects(*this, plane);     }
    virtual Result Intersects(Poly const & poly) const override           { return Intersectable::Intersects(*this, poly);      }
    virtual Result Intersects(Sphere const & sphere) const override       { return Intersectable::Intersects(*this, sphere);    }
    virtual Result Intersects(Cone const & cone) const override           { return Intersectable::Intersects(*this, cone);      }
    virtual Result Intersects(AABox const & aabox) const override         { return Intersectable::Intersects(*this, aabox);     }
    virtual Result Intersects(Box const & box) const override             { return Intersectable::Intersects(*this, box);       }
    virtual Result Intersects(Frustum const & frustum) const override     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    Vector3 m_C;        //!< Location of the center
    float m_R;          //!< Radius
};

#endif // !defined(MYMATH_SPHERE_H)
