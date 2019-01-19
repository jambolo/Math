/** @file *//********************************************************************************************************

                                                    Box.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Box.cpp#9 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Box.h"

#include "Vector3.h"
#include "Matrix33.h"
#include "Matrix44.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	position	Location of the box's origin
//! @param	size		Size of the box
//! @note	The position and size values are adjusted so that each element of the size is non-negative. This does
//!			change the effective position and size of the box, but it does change which corner is the origin.

AABox::AABox( Vector3 const & position, Vector3 const & size )
	: m_Position( position ), m_Scale( size )
{
	// Normalize

	if ( m_Scale.m_X < 0.f )
	{
		m_Position.m_X += m_Scale.m_X;
		m_Scale.m_X = -m_Scale.m_X;
	}

	if ( m_Scale.m_Y < 0.f )
	{
		m_Position.m_Y += m_Scale.m_Y;
		m_Scale.m_Y = -m_Scale.m_Y;
	}

	if ( m_Scale.m_Z < 0.f )
	{
		m_Position.m_Z += m_Scale.m_Z;
		m_Scale.m_Z = -m_Scale.m_Z;
	}

}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @note	Boxes may not have a scale of 0 along any axis.

Box::Box( Matrix33 const & orientation, Vector3 const & position, Vector3 const & scale )
	: m_Position( position ), m_Scale( scale ), m_InverseOrientation( orientation )
{
	assert( !Math::IsCloseToZero( m_Scale.m_X ) );
	assert( !Math::IsCloseToZero( m_Scale.m_Y ) );
	assert( !Math::IsCloseToZero( m_Scale.m_Z ) );

	// Make sure that the inverse is the same as the transpose.

	assert( m_InverseOrientation.IsOrthonormal() );

	m_InverseOrientation.Transpose(); 
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! This function constructs an oriented box given a matrix which transforms an axis-aligned unit cube at the origin
//! to the desired box
//!
//! @note	Boxes may not have a scale of 0 along any axis.

Box::Box( Matrix44 const & transform )
{
	m_Position = Vector3( transform.m_Xw, transform.m_Yw, transform.m_Zw );

	Vector3	x( transform.m_Xx, transform.m_Xy, transform.m_Xz );
	Vector3	y( transform.m_Yx, transform.m_Yy, transform.m_Yz );
	Vector3	z( transform.m_Zx, transform.m_Zy, transform.m_Zz );

	m_Scale		= Vector3( x.Length(), y.Length(), z.Length() );

	assert( !Math::IsCloseToZero( m_Scale.m_X ) );
	assert( !Math::IsCloseToZero( m_Scale.m_Y ) );
	assert( !Math::IsCloseToZero( m_Scale.m_Z ) );

	x *= 1.f / m_Scale.m_X;
	y *= 1.f / m_Scale.m_Y;
	z *= 1.f / m_Scale.m_Z;

	m_InverseOrientation = Matrix33( x.m_X, y.m_X, z.m_X,
									 x.m_Y, y.m_Y, z.m_Y,
									 x.m_Z, y.m_Z, z.m_Z );

	assert( m_InverseOrientation.IsOrthonormal() );
}
