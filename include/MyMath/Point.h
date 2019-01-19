/** @file *//********************************************************************************************************

                                                       Point.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Point.h#13 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "Intersectable.h"
#include "Vector3.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! A point that can detect and compute intersections with other intersectable objects.
//
//! @ingroup Geometry
//!

class Point : public Intersectable, public Vector3
{
public:

	//! Constructor
	Point()														{}

	//! Constructor
	Point( float x, float y, float z )	: Vector3( x, y, z )	{}

	//! Constructor
	Point( float const v[ 3 ] )			: Vector3( v )			{}

	//! Conversion
	Point( Vector3 const & v )			: Vector3( v )			{}

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

	//! @name Overrides Vector3
	//@{
	//	float			Length2()							const;
	//	float			Length()							const;
	//	float			ILength()							const;
	//	bool			IsNormalized()						const;
	//	Vector3 const &	Negate();
	//	Vector3 const &	Normalize();
	//	Vector3 const &	Add( Vector3 const & b );
	//	Vector3 const &	Subtract( Vector3 const & b );
	//	Vector3 const &	Scale( float scale );
	//	Vector3 const &	Transform( Matrix43 const & m );
	//	Vector3 const &	Transform( Matrix33 const & m );
	//	Vector3 const &	Rotate( Vector3 const & axis, float angle );
	//	Vector3 const &	Rotate( Quaternion const & q );
	//	Vector3 const &	operator +=( Vector3 const & b );
	//	Vector3 const &	operator -=( Vector3 const & b );
	//	Vector3 const &	operator *=( float scale );
	//	Vector3 const &	operator *=( Matrix43 const & m );
	//	Vector3 const &	operator *=( Matrix33 const & m );
	//	Vector3			operator -()						const;
	//	Vector3			operator +( Vector3 const & b )		const;
	//	Vector3			operator -( Vector3 const & b )		const;
	//	Vector3			operator *( Matrix43 const & m )	const;
	//	Vector3			operator *( Matrix33 const & m )	const;
	//@}
};
