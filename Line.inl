/** @file *//********************************************************************************************************

                                                       Line.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Line.inl#12 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include "Line.h"

#include "Misc/Assert.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	m	Direction of the line. The vector must be normalized.
//! @param	b	A point on the line

inline Line::Line( Vector3 const & m, Vector3 const & b )
	: m_M( m ), m_B( b )
{
	assert( m.IsNormalized() );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a line that is colinear with the ray.
//!
//! @param ray	A ray

inline Line::Line( Ray const & ray )
	: m_M( ray.m_M ), m_B( ray.m_B )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a line that is colinear with the segment.
//!
//! @param segment	A line segment

inline Line::Line( Segment const & segment )
	: m_M( segment.m_M ), m_B( segment.m_B )
{
	assert( !Math::IsCloseToZero( m_M.Length() ) );
	m_M.Normalize();
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	m	Direction of the ray. The vector must be normalized.
//! @param	b	The endpoint of the ray

inline Ray::Ray( Vector3 const & m, Vector3 const & b )
	: m_M( m ), m_B( b )
{
	assert( m.IsNormalized() );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs a line segment between two points.
//!
//! @param	p0,p1	Endpoints

inline Segment::Segment( Vector3 const & p0, Vector3 const & p1 )
{
	m_M = p1 - p0;
	m_B = p0;
}



/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	m		Direction of the line segment. The vector must be normalized.
//! @param	b		The endpoint of the line segment when t == 0
//! @param	length	The length of the segment

inline Segment::Segment( Vector3 const & m, Vector3 const & b, float length )
{
	assert( m.IsNormalized() );
	assert( !Math::IsCloseToZero( length ) );

	m_M = m * length;
	m_B = b;
}


