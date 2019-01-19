/** @file *//********************************************************************************************************

                                                       Sphere.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Sphere.h#12 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "Intersectable.h"
#include "Vector3.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! A sphere that can detect and compute intersections with other intersectable objects.
//
//! @ingroup Geometry
//!

class Sphere : public Intersectable
{
public:

	//! Constructor
	Sphere()													{}

	//! Constructor
	Sphere( Vector3 const & c, float r ) : m_C( c ), m_R( r )	{}

	//! Destructor
	~Sphere()													{}

	//! @name Overrides Intersectable
	//@{
	virtual IntersectionClass IntersectedBy( Intersectable const * pI ) const	{ return pI->Intersects( *this );						}
	virtual IntersectionClass Intersects( Point const & point ) const			{ return Intersectable::Intersects( *this, point );		}
	virtual IntersectionClass Intersects( Line const & line ) const				{ return Intersectable::Intersects( *this, line );		}
	virtual IntersectionClass Intersects( Ray const & ray ) const				{ return Intersectable::Intersects( *this, ray );		}
	virtual IntersectionClass Intersects( Segment const & segment ) const		{ return Intersectable::Intersects( *this, segment );	}
	virtual IntersectionClass Intersects( Plane const & plane ) const			{ return Intersectable::Intersects( *this, plane );		}
	virtual IntersectionClass Intersects( Poly const & poly ) const				{ return Intersectable::Intersects( *this, poly );		}
	virtual IntersectionClass Intersects( Sphere const & sphere ) const			{ return Intersectable::Intersects( *this, sphere );	}
	virtual IntersectionClass Intersects( Cone const & cone ) const				{ return Intersectable::Intersects( *this, cone );		}
	virtual IntersectionClass Intersects( AABox const & aabox ) const			{ return Intersectable::Intersects( *this, aabox );		}
	virtual IntersectionClass Intersects( Box const & box ) const				{ return Intersectable::Intersects( *this, box );		}
	virtual IntersectionClass Intersects( Frustum const & frustum ) const		{ return Intersectable::Intersects( *this, frustum );	}
	//@}

	Vector3		m_C;	//!< Location of the center
	float		m_R;	//!< Radius
};
