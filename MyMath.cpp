/** @file *//********************************************************************************************************

                                                       Math.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Math.cpp#4 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Math.h"
#include "Constants.h"

namespace Math
{


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	n	Number to factorialize (<i>n</i> > 0)

double Stirling( double n )
{
//	double const	f	= SQRT_OF_TWO_PI * pow( n, n + .5 ) * exp( -n )
//	double const	f	= SQRT_OF_TWO_PI * sqrt( n ) * pow( n/E, n )
	double const	f	= SQRT_OF_TWO_PI * exp( ( n + .5 ) * log( n ) - n );

	return f;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	z00		Value when y = 0 and x = 0
//! @param	z01		Value when y = 0 and x = 1
//! @param	z10		Value when y = 1 and x = 0
//! @param	z11		Value when y = 1 and x = 1
//! @param	x		Position to interpolate. The valid range is [0,1];
//! @param	y		Position to interpolate. The valid range is [0,1];
//!
//! @return		The interpolated value

float Lerp2D( float z00, float z01, float z10, float z11, float x, float y )
{
	assert( x >= 0.0f && x <= 1.0f );
	assert( y >= 0.0f && y <= 1.0f );

	float const		z0x	= Lerp( z00, z01, x );
	float const		z1x	= Lerp( z10, z11, x );

	return Lerp( z0x, z1x, y );
}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @param	w000	Value when z = 0 and y = 0 and x = 0
//! @param	w001	Value when z = 0 and y = 0 and x = 1
//! @param	w010	Value when z = 0 and y = 1 and x = 0
//! @param	w011	Value when z = 0 and y = 1 and x = 1
//! @param	w100	Value when z = 1 and y = 0 and x = 0
//! @param	w101	Value when z = 1 and y = 0 and x = 1
//! @param	w110	Value when z = 1 and y = 1 and x = 0
//! @param	w111	Value when z = 1 and y = 1 and x = 1
//! @param	x		Position to interpolate. The valid range is [0,1];
//! @param	y		Position to interpolate. The valid range is [0,1];
//! @param	z		Position to interpolate. The valid range is [0,1];
//!
//! @return		The interpolated value

float Lerp3D( float w000, float w001, float w010, float w011, float w100, float w101, float w110, float w111,
			  float x, float y, float z )
{
	assert( x >= 0.0f && x <= 1.0f );
	assert( y >= 0.0f && y <= 1.0f );
	assert( z >= 0.0f && z <= 1.0f );

	float const		w0yx	= Lerp2D( w000, w001, w010, w011, x, y );
	float const		w1yx	= Lerp2D( w100, w101, w110, w111, x, y );

	return Lerp( w0yx, w1yx, z );
}


} // namespace Math