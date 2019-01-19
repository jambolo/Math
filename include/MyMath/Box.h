/** @file *//********************************************************************************************************

                                                        Box.h

                                            Copyright 2002, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Box.h#12 $

    $NoKeywords: $

 *********************************************************************************************************************/

#pragma once

#include "Intersectable.h"
#include "Matrix33.h"
#include "Vector3.h"

//! Axis-aligned box that can detect and compute intersections with other intersectables.
//
//! @ingroup Geometry
//!

class AABox : public Intersectable
{
public:

    //! Default constructor
    AABox() {}

    //! Constructor
    AABox(Vector3 const & position, Vector3 const & size);

    //! Destructor
    ~AABox() {}

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

    Vector3 m_Position;     //!< Location of the origin of the box
    Vector3 m_Scale;        //!< Size of the box
};

//! Oriented box that can detect and compute intersections with other intersectables.
//
//! @ingroup Geometry
//!

class Box : public Intersectable
{
public:

    //! Constructor
    Box(Matrix33 const & orientation, Vector3 const & position, Vector3 const & scale);

    //! Conversion
    explicit Box(Matrix44 const & transform);

    //! Destructor
    ~Box() {}

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

    //! Returns the orientation of the box
    Matrix33 GetOrientation() const { return Matrix33(m_InverseOrientation).Transpose();  }

    Matrix33 m_InverseOrientation;      //!< Inverse of the orientation of the box
    Vector3 m_Position;                 //!< Location of the origin of the box
    Vector3 m_Scale;                    //!< Size of the box
};
