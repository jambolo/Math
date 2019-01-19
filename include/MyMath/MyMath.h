#pragma once

#include "Constants.h"
#include <cmath>
#include <cassert>

// Group definitions for doxygen

//! @defgroup	Geometry		Geometric Objects
//! A collection of various geometric objects.

//! @defgroup	Matrices		Matrices
//! Matrices and related functions

//! @defgroup	Vectors			Vectors
//! Vectors and related functions

//! @defgroup	Miscellaneous	Miscellaneous
//! Miscellaneous

//! Math library

namespace Math
{

//! @defgroup	Conversion	Units Conversion
//! @ingroup	Miscellaneous
//@{

//! Converts radians to degrees.
inline double ToDegrees( double radians )
{
	return radians * DEGREES_PER_RADIAN;
}

//! Converts radians to degrees.
inline float ToDegrees( float radians )
{
	return radians * float( DEGREES_PER_RADIAN );
}

//! Converts degrees to radians.
inline double ToRadians( double degrees )
{
	return degrees * RADIANS_PER_DEGREE;
}

//! Converts degrees to radians.
inline float ToRadians( float degrees )
{
	return degrees * float( RADIANS_PER_DEGREE );
}

//@}

//! @defgroup	FloatComparison		Floating-Point Comparison
//! @ingroup	Miscellaneous
//@{

//! @name	Floating-Point Comparison Tolerances
//! The goal of having a tolerance is to detect when two numbers are close enough that the difference between them
//! will not have enough precision to give meaningful results. 4 bits of precision is pretty useless so the tolerance
//! values here are calculated to give 4 bits of slack for numbers near 1 and -1. If you are using numbers that are
//! <b>much</b> bigger or <b>much</b> smaller than 1, you should not use these defaults, or you should use
//! IsRelativelyCloseTo().

//@{
double const	DEFAULT_FLOAT_TOLERANCE		= 9.5367431640625000e-7;	// 2** -(24-4)
double const	DEFAULT_DOUBLE_TOLERANCE	= 1.7763568394002505e-15;	// 2** -(53-4)
//@}

//! @name	Normalization Tolerances
//! When testing if a vector is normalized (e.i. the length is 1), it is important to allow some error. Generally, a
//! system can operate well even if the error is fairly high (compared to the available precision). Also, when the
//! length of a vector is not close enough to 1, the vector must be renormalized and renormalization is a
//! relatively expensive operation.

//@{
double const	DEFAULT_FLOAT_NORMALIZED_TOLERANCE		= .0001;
double const	DEFAULT_DOUBLE_NORMALIZED_TOLERANCE		= .0000001;
//@}

//! @name	Orthonormalization Tolerances
//! When testing if a matrix is orthonormal, it is important to allow some error. Generally, a system can operate
//! well even when the error is fairly high (compared to the available precision). Also, when the matrix is not
//! orthonormal, it generally must be re-orthonormalized, and orthonormalization is a very expensive operation.

//@{
double const	DEFAULT_FLOAT_ORTHONORMAL_TOLERANCE		= .001;
double const	DEFAULT_DOUBLE_ORTHONORMAL_TOLERANCE	= .00001;
//@}


//! Returns true if @a x is very close to 0.
inline bool IsCloseToZero( double x, double tolerance = DEFAULT_FLOAT_TOLERANCE )
{
	return ( std::fabs( x ) < tolerance );
}

//! Returns true if @a x is very close to @a y in absolute terms.
//! @note	When comparing the @e squares of two values to determine if the values are close, you should change the
//!			tolerance to 2<em>yT</em>. The actual tolerance is 2<em>yT</em> +/- <em>T</em>**2, but the +/- makes it
//!			complicated and <em>T</em>**2 is generally negligible.
inline bool IsCloseTo( double x, double y, double tolerance = DEFAULT_FLOAT_TOLERANCE )
{
	return IsCloseToZero( x - y, tolerance );
}

//! Returns true if @a x is very close to @a y relative to the value of @a y.
//! @note	When comparing the @e squares of two values to determine if the values are close, you should change the
//!			tolerance to 2T. The actual tolerance is 2<em>T</em> +/- <em>T</em>**2, but the +/- makes it
//!			complicated and <em>T</em>**2 is generally negligible.
inline bool IsRelativelyCloseTo( double x, double y, double tolerance = DEFAULT_FLOAT_TOLERANCE )
{
	return IsCloseTo( x, y, tolerance * y );
}

//@}

//! @defgroup	Functions	Miscellaneous Functions
//! @ingroup	Miscellaneous
//@{

//! Returns <i>n</i>! computed using Stirling's formula
double Stirling( double n );

//! Returns the linear interpolation between two values
//
//! @param	y0	Value when x = 0
//! @param	y1	Value when x = 1
//! @param	x	Position to interpolate. The valid range is [0,1];
//!
//! @return		The interpolated value

inline float Lerp( float y0, float y1, float x )
{
	assert( x >= 0.0f && x <= 1.0f );
	return ( y0 + x * ( y1 - y0 ) );
}

//! Returns the linear interpolation between 4 values in 2D
float Lerp2D( float z00, float z01, float z10, float z11, float x, float y );

//! Returns the linear interpolation between 8 values in 3D
float Lerp3D( float w000, float w001, float w010, float w011, float w100, float w101, float w110, float w111,
			  float x, float y, float z );


//@}


} // namespace Math
