/** @file *//********************************************************************************************************

                                                        Cone.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Cone.h#5 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "Intersectable.h"

#include "Constants.h"
#include "Vector3.h"
#include "Misc/Assert.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! A cone that can detect and compute intersections with other intersectable objects.
//
//! @ingroup Geometry
//!

class Cone : public Intersectable
{
public:

	//! Constructor
	Cone()															{}

	//! Constructor
	Cone( Vector3 const & v, Vector3 const & d, float a )
		: m_V( v ), m_D( d ), m_A( cosf( a ) )
	{
		assert( a > 0.f && a < Math::PI_OVER_2 );
	}

	//! Destructor
	~Cone()															{}

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

	// The cone equation is:  D dot ( X - V ) >= |X - V| * cos( a )

	Vector3		m_V;	//!< The cone's vertex
	Vector3		m_D;	//!< The direction of the cone
	float		m_A;	//!< The cosine of the angle between the side and the center line of the cone ( 0 < m_Cos < 1 )
};
