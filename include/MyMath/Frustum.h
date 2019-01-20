#pragma once

#if !defined(MYMATH_FRUSTUM_H)
#define MYMATH_FRUSTUM_H

#include "Intersectable.h"
#include "Plane.h"

//! A frustum that can detect and compute intersections with other intersectables.
//
//! @ingroup Geometry
//!

class Frustum : public Intersectable
{
public:

    //! Index for each side of the frustum
    enum SideIndex
    {
        LEFT_SIDE = 0,
        RIGHT_SIDE,
        TOP_SIDE,
        BOTTOM_SIDE,
        FRONT_SIDE,
        BACK_SIDE
    };
    static int constexpr NUM_SIDES = BACK_SIDE - LEFT_SIDE + 1;

    //! Constructor
    Frustum() = default;

    //! Constructor
    Frustum(Plane const & left, Plane const & right,
            Plane const & bottom, Plane const & top,
            Plane const & n, Plane const & f);

    //! Destructor
    virtual ~Frustum() override = default;

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

    Plane m_Sides[NUM_SIDES]; //!< Sides
};

#endif // !defined(MYMATH_FRUSTUM_H)
