/** @file *//********************************************************************************************************

                                                     Matrix33d.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix33d.inl#5 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Matrix33d.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix33d::Matrix33d( double Xx, double Xy, double Xz,
							 double Yx, double Yy, double Yz,
							 double Zx, double Zy, double Zz )

	: m_Xx( Xx ), m_Xy( Xy ), m_Xz( Xz ),
	  m_Yx( Yx ), m_Yy( Yy ), m_Yz( Yz ),
	  m_Zx( Zx ), m_Zy( Zy ), m_Zz( Zz )
{
}


/********************************************************************************************************************/

/********************************************************************************************************************/

inline Vector3d const &	Matrix33d::GetX() const
{
	return *reinterpret_cast< Vector3d const * >( &m_Xx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3d const &	Matrix33d::GetY() const
{
	return *reinterpret_cast< Vector3d const * >( &m_Yx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3d const &	Matrix33d::GetZ() const
{
	return *reinterpret_cast< Vector3d const * >( &m_Zx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix33d & Matrix33d::operator *=( Matrix33d const & b )
{
	return PostConcatenate( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline 	Matrix33d Matrix33d::operator ~() const
{
	return Matrix33d( *this ).Invert();
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix33d Matrix33d::Identity()
{
	return Matrix33d( 1.0, 0.0, 0.0,
					  0.0, 1.0, 0.0,
					  0.0, 0.0, 1.0 );
}
