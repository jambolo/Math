#pragma once

#if !defined(MYMATH_BOX_H)
#define MYMATH_BOX_H

#include "Intersectable.h"
#include "Matrix33.h"
#include "Vector3.h"

//! Axis-aligned box that can detect and compute intersections with other intersectables.
//!
//! @ingroup Geometry
//!

class AABox : public Intersectable
{
public:

    //! Default constructor
    AABox() = default;

    //! Constructor.
    AABox(Vector3 const & position, Vector3 const & size);

    //! Destructor.
    virtual ~AABox() override = default;

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

    Vector3 m_Position;     //!< Location of the origin of the box
    Vector3 m_Scale;        //!< Size of the box
};

//! Oriented box that can detect and compute intersections with other intersectables.
//!
//! @ingroup Geometry
//!

class Box : public Intersectable
{
public:

    //! Constructor.
    Box(Matrix33 const & orientation, Vector3 const & position, Vector3 const & scale);

    //! Conversion
    explicit Box(Matrix44 const & transform);

    //! Destructor.
    virtual ~Box() override = default;

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

    //! Returns the orientation of the box
    Matrix33 GetOrientation() const { return Matrix33(m_InverseOrientation).Transpose();  }

    Matrix33 m_InverseOrientation;      //!< Inverse of the orientation of the box
    Vector3 m_Position;                 //!< Location of the origin of the box
    Vector3 m_Scale;                    //!< Size of the box
};

#endif // !defined(MYMATH_BOX_H)
