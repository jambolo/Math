/** @file *//********************************************************************************************************

                                                      Plane.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Plane.inl#13 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Plane.h"

#include "Vector3.h"
#include "Point.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Plane::Plane()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a plane whose distance from the origin is the length of @a distance, and whose normal
//! points in the direction of @a distance.
//!
//! @param	distance	A vector describing the orientation of the plane and its distance from the origin

inline Plane::Plane( Vector3 const & distance )
{
	float const	length	= distance.Length();

	if ( !Math::IsCloseToZero( length ) )
	{
		m_D = -length;
		m_N = distance;
		m_N *= 1.f / length;
	}
	else
	{
		m_D = 0.;
		m_N = Vector3::XAxis();
	}
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a plane with the given normal and distance from the origin.
//!
//! @param	normal	The plane's normal. This vector must be normalized.
//! @param	d		Distance from the origin (in the direction of the normal)

inline Plane::Plane( Vector3 const & normal, float d )
	: m_N( normal ), m_D( -d )
{
	assert( normal.IsNormalized() );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a plane given the normal and the position of a point in the plane.
//!
//! @param	normal		The plane's normal. This vector must be normalized.
//! @param	point		The position of a point in the plane

inline Plane::Plane( Vector3 const & normal, Point const & point )
	: m_N( normal ), m_D( Dot( normal, point ) )
{
	assert( normal.IsNormalized() );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a plane that is described by the formula <em>a</em>x + <em>b</em>y + <em>c</em>z +
//! <em>d</em> = 0. The function normalizes the parameters before storing them.
//!
//! @param	a,b,c,d		Plane parameters

inline Plane::Plane( float a, float b, float c, float d )
	: m_N( a, b, c ), m_D( d )
{
	assert( !Math::IsCloseToZero( m_N.Length() ) );

	float const	ilength	= m_N.ILength();

	m_D *= ilength;
	m_N *= ilength;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Plane::~Plane()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	point	Point to reflect

inline Point Plane::Reflect( Point const & point ) const
{
	return point - m_N * ( DirectedDistance( point ) * 2.f );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	v	Vector to reflect

inline Vector3 Plane::ReflectVector( Vector3 const & v ) const
{
	return v - m_N * ( Dot( m_N, v ) * 2.f );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	point	Point to project

inline Point Plane::Project( Point const & point ) const
{
	return Point( point - m_N * DirectedDistance( point ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	point	Point to project
//! @param	v		Vector to project along

inline Point Plane::Project( Point const & point, Vector3 const & v ) const
{
	float const	nDotV	= Dot( m_N, v );

	return ( Math::IsCloseToZero( nDotV ) ) ?
				point - v * DirectedDistance( point ) :
				point - v * ( DirectedDistance( point ) / nDotV );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	v		Vector to project

inline Vector3 Plane::ProjectVector( Vector3 const & v ) const
{
	return v - m_N * Dot( m_N, v );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline bool Plane::IsInFrontOf( Point const & v ) const
{
	return DirectedDistance( v ) > 0.f;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline bool Plane::IsBehind( Point const & v ) const
{
	return DirectedDistance( v ) < 0.f;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline float Plane::DirectedDistance( Point const & point ) const
{
	return ( Dot( m_N, point ) + m_D );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HalfSpace::HalfSpace()
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HalfSpace::HalfSpace( Plane const & plane )
	: m_Plane( plane )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline HalfSpace::~HalfSpace()
{
}
