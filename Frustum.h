/** @file *//********************************************************************************************************

                                                      Frustum.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Frustum.h#14 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "Intersectable.h"
#include "Plane.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

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
		LEFT_SIDE	= 0,
		RIGHT_SIDE,
		TOP_SIDE,
		BOTTOM_SIDE,
		NEAR_SIDE,
		FAR_SIDE,

		NUM_SIDES
	};

	//! Constructor
	Frustum();

	//! Constructor
	Frustum( Plane const & left, Plane const & right,
			 Plane const & bottom, Plane const & top,
			 Plane const & n, Plane const & f );

	//! Destructor
	~Frustum() {}

	//! @name Overrides Intersectable
	//@{
	virtual IntersectionClass IntersectedBy( Intersectable const * pI ) const	{ return pI->Intersects( *this );						}
	virtual IntersectionClass Intersects( Point const & point ) const			{ return Intersectable::Intersects( *this, point );		}
	virtual IntersectionClass Intersects( Line const & line ) const				{ return Intersectable::Intersects( *this, line );		}
	virtual IntersectionClass Intersects( Ray const & ray ) const				{ return Intersectable::Intersects( *this, ray );		}
	virtual IntersectionClass Intersects( Segment const & segment ) const		{ return Intersectable::Intersects( *this, segment );	}
	virtual IntersectionClass Intersects( Plane const & plane ) const			{ return Intersectable::Intersects( *this, plane );		}
	virtual IntersectionClass Intersects( HalfSpace const & halfspace ) const	{ return Intersectable::Intersects( *this, halfspace );	}
	virtual IntersectionClass Intersects( Poly const & poly ) const				{ return Intersectable::Intersects( *this, poly );		}
	virtual IntersectionClass Intersects( Sphere const & sphere ) const			{ return Intersectable::Intersects( *this, sphere );	}
	virtual IntersectionClass Intersects( Cone const & cone ) const				{ return Intersectable::Intersects( *this, cone );		}
	virtual IntersectionClass Intersects( AABox const & aabox ) const			{ return Intersectable::Intersects( *this, aabox );		}
	virtual IntersectionClass Intersects( Box const & box ) const				{ return Intersectable::Intersects( *this, box );		}
	virtual IntersectionClass Intersects( Frustum const & frustum ) const		{ return Intersectable::Intersects( *this, frustum );	}
	//@}

	Plane	m_Sides[ NUM_SIDES ];			//!< Sides
};
