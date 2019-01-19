/** @file *//********************************************************************************************************

                                                     Matrix44d.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix44d.inl#5 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Matrix44d.h"

#include "Vector3d.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix44d::Matrix44d( double Xx, double Xy, double Xz, double Xw,
							 double Yx, double Yy, double Yz, double Yw,
							 double Zx, double Zy, double Zz, double Zw,
							 double Tx, double Ty, double Tz, double Tw )

	: m_Xx( Xx ), m_Xy( Xy ), m_Xz( Xz ), m_Xw( Xw ),
	  m_Yx( Yx ), m_Yy( Yy ), m_Yz( Yz ), m_Yw( Yw ),
	  m_Zx( Zx ), m_Zy( Zy ), m_Zz( Zz ), m_Zw( Zw ),
	  m_Tx( Tx ), m_Ty( Ty ), m_Tz( Tz ), m_Tw( Tw )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix44d::Matrix44d( Vector3d const & x,
							 Vector3d const & y,
							 Vector3d const & z,
							 Vector3d const & t/* = Vector3d::Origin()*/ )
	: m_Xx( x.m_X ), m_Xy( x.m_Y ), m_Xz( x.m_Z ), m_Xw( 0.0 ),
	  m_Yx( y.m_X ), m_Yy( y.m_Y ), m_Yz( y.m_Z ), m_Yw( 0.0 ),
	  m_Zx( z.m_X ), m_Zy( z.m_Y ), m_Zz( z.m_Z ), m_Zw( 0.0 ),
	  m_Tx( t.m_X ), m_Ty( t.m_Y ), m_Tz( t.m_Z ), m_Tw( 1.0 )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector4d const &	Matrix44d::GetX() const
{
	return *reinterpret_cast< Vector4d const * >( &m_Xx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector4d const &	Matrix44d::GetY() const
{
	return *reinterpret_cast< Vector4d const * >( &m_Yx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector4d const &	Matrix44d::GetZ() const
{
	return *reinterpret_cast< Vector4d const * >( &m_Zx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector4d const &	Matrix44d::GetT() const
{
	return *reinterpret_cast< Vector4d const * >( &m_Tx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix44d & Matrix44d::operator *=( Matrix44d const & b )
{
	return PostConcatenate( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline 	Matrix44d Matrix44d::operator ~() const
{
	return Matrix44d( *this ).Invert();
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix44d Matrix44d::Identity()
{
	return Matrix44d( 1.0, 0.0, 0.0, 0.0,
					  0.0, 1.0, 0.0, 0.0,
					  0.0, 0.0, 1.0, 0.0,
					  0.0, 0.0, 0.0, 1.0 );
}