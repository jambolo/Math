/** @file *//********************************************************************************************************

                                                     Vector4d.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector4d.cpp#7 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Vector4d.h"

#include "Matrix43d.h"
#include "Matrix44d.h"
#include "Quaternion.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @note	In order to multiply, a 4th row/column with a value of [0, 0, 0, 1] is implicit.

Vector4d const & Vector4d::Transform( Matrix43d const & m )
{
	double const	x	= m_X;
	double const	y	= m_Y;
	double const	z	= m_Z;
	double const	w	= m_W;

//	m_X = x * m.m_Xx + y * m.m_Yx + z * m.m_Zx + w * m.m_Tx;
//	m_Y = x * m.m_Xy + y * m.m_Yy + z * m.m_Zy + w * m.m_Ty;
//	m_Z = x * m.m_Xz + y * m.m_Yz + z * m.m_Zz + w * m.m_Tz;
//	m_W = x * 0      + y * 0      + z * 0      + w * 1;

	// Optimized for cache coherency

	m_X  = x * m.m_Xx;
	m_Y  = x * m.m_Xy;
	m_Z  = x * m.m_Xz;

	m_X += y * m.m_Yx;
	m_Y += y * m.m_Yy;
	m_Z += y * m.m_Yz;

	m_X += z * m.m_Zx;
	m_Y += z * m.m_Zy;
	m_Z += z * m.m_Zz;

	m_X += w * m.m_Tx;
	m_Y += w * m.m_Ty;
	m_Z += w * m.m_Tz;

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Vector4d const & Vector4d::Transform( Matrix44d const & m )
{
	double const	x	= m_X;
	double const	y	= m_Y;
	double const	z	= m_Z;
	double const	w	= m_W;

//	m_X = x * m.m_Xx + y * m.m_Yx + z * m.m_Zx + w * m.m_Tx;
//	m_Y = x * m.m_Xy + y * m.m_Yy + z * m.m_Zy + w * m.m_Ty;
//	m_Z = x * m.m_Xz + y * m.m_Yz + z * m.m_Zz + w * m.m_Tz;
//	m_W = x * m.m_Xw + y * m.m_Yw + z * m.m_Zw + w * m.m_Tw;

	// Optimized for cache coherency

	m_X  = x * m.m_Xx;
	m_Y  = x * m.m_Xy;
	m_Z  = x * m.m_Xz;
	m_W  = x * m.m_Xw;

	m_X += y * m.m_Yx;
	m_Y += y * m.m_Yy;
	m_Z += y * m.m_Yz;
	m_W += y * m.m_Yw;

	m_X += z * m.m_Zx;
	m_Y += z * m.m_Zy;
	m_Z += z * m.m_Zz;
	m_W += z * m.m_Zw;

	m_X += w * m.m_Tx;
	m_Y += w * m.m_Ty;
	m_Z += w * m.m_Tz;
	m_W += w * m.m_Tw;

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @param	axis	Axis to rotate around
//! @param	angle	Angle of rotation

Vector4d const & Vector4d::Rotate( Vector4d const & axis, double angle )
{
	assert( axis.IsNormalized() );

	double const	x	= m_X;
	double const	y	= m_Y;
	double const	z	= m_Z;

	double const	s	= sin( angle );
	double const	c	= cos( angle );
	double const	c1	= 1. - c;

	double const	xx	= axis.m_X * axis.m_X * c1;
	double const	xy	= axis.m_X * axis.m_Y * c1;
	double const	xz	= axis.m_X * axis.m_Z * c1;
	double const	xw	= axis.m_X * s;
					
	double const	yy	= axis.m_Y * axis.m_Y * c1;
	double const	yz	= axis.m_Y * axis.m_Z * c1;
	double const	yw	= axis.m_Y * s;
					
	double const	zz	= axis.m_Z * axis.m_Z * c1;
	double const	zw	= axis.m_Z * s;

//	Matrix44d const	r( xx + c , xy - zw, xz + yw, 0.,
//					   xy + zw, yy + c , yz - xw, 0.,
//					   xz - yw, yz + xw, zz + c,  0.,
//					   0.,      0.,      0.,      1. );
//
//	Transform( r );

	m_X = x * ( xx + c  ) + y * ( xy + zw ) + z * ( xz - yw );
	m_Y = x * ( xy - zw ) + y * ( yy + c  ) + z * ( yz + xw );
	m_Z = x * ( xz + yw ) + y * ( yz - xw ) + z * ( zz + c  );

	return *this;
}

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Vector4d const & Vector4d::Rotate( Quaternion const & q )
{
//	Transform( Matrix44d( q.GetRotationMatrix33() ) );

	assert( q.IsNormalized() );

	double const	x	= m_X;
	double const	y	= m_Y;
	double const	z	= m_Z;

	double const	xx	= q.m_X * q.m_X;
	double const	xy	= q.m_X * q.m_Y;
	double const	xz	= q.m_X * q.m_Z;
	double const	xw	= q.m_X * q.m_W;
					
	double const	yy	= q.m_Y * q.m_Y;
	double const	yz	= q.m_Y * q.m_Z;
	double const	yw	= q.m_Y * q.m_W;
					
	double const	zz	= q.m_Z * q.m_Z;
	double const	zw	= q.m_Z * q.m_W;

	m_X += 2.0 * -x * ( yy + zz ) + y * ( xy - zw ) + z * ( xz + yw );
	m_Y += 2.0 *  x * ( xy + zw ) - y * ( xx + zz ) + z * ( yz - xw );
	m_Z += 2.0 *  x * ( xz - yw ) + y * ( yz + xw ) - z * ( xx + yy );

	return *this;
}


