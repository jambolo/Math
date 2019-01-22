#pragma once

#if !defined(MYMATH_CONE_H)
#define MYMATH_CONE_H

#include "Intersectable.h"

#include "Constants.h"
#include "Misc/Assert.h"
#include "Vector3.h"
#include <cassert>
#include <DirectXMath.h>

//! A cone that can detect and compute intersections with other intersectable objects.
//
//! @ingroup Geometry
//!

class Cone : public Intersectable
{
public:

    //! Constructor
    Cone() = default;

    //! Constructor
    Cone(Vector3 const & v, Vector3 const & d, float a)
        : m_V(v)
        , m_D(d)
        , m_A(cosf(a))
    {
        assert(a > 0.f && a < DirectX::XM_PIDIV2);
    }

    //! Destructor
    virtual ~Cone() override = default;

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

    // The cone equation is:  D dot ( X - V ) >= |X - V| * cos( a )

    Vector3 m_V;    //!< The cone's vertex
    Vector3 m_D;    //!< The direction of the cone
    float m_A;      //!< The cosine of the angle between the side and the center line of the cone ( 0 < m_Cos < 1 )
};

#endif // !defined(MYMATH_CONE_H)
