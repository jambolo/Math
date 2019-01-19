/** @file *//********************************************************************************************************

                                                    Matrix33.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix33.cpp#13 $

	$NoKeywords: $

 ********************************************************************************************************************/


#include "PrecompiledHeaders.h"

#include "Matrix33.h"

#include "Vector3.h"
#include "Matrix33d.h"
#include "Matrix43.h"
#include "Matrix44.h"
#include "Determinant.h"

#include <utility>

using namespace std;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33::Matrix33( float const * pM )
{
	memcpy( m_M, pM, sizeof( m_M ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33::Matrix33( Vector3 const & x, Vector3 const & y, Vector3 const & z )
	: m_Xx( x.m_X ), m_Xy( x.m_Y ), m_Xz( x.m_Z ),
	  m_Yx( y.m_X ), m_Yy( y.m_Y ), m_Yz( y.m_Z ),
	  m_Zx( z.m_X ), m_Zy( z.m_Y ), m_Zz( z.m_Z )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33::Matrix33( Matrix33d const & m33d )
	: m_Xx( float( m33d.m_Xx ) ), m_Xy( float( m33d.m_Xy ) ), m_Xz( float( m33d.m_Xz ) ),
	  m_Yx( float( m33d.m_Yx ) ), m_Yy( float( m33d.m_Yy ) ), m_Yz( float( m33d.m_Yz ) ),
	  m_Zx( float( m33d.m_Zx ) ), m_Zy( float( m33d.m_Zy ) ), m_Zz( float( m33d.m_Zz ) )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! This function contructs a 3x3 matrix by extracting it from the 4x3 matrix.

Matrix33::Matrix33( Matrix43 const & m43 )
	: m_Xx( m43.m_Xx ), m_Xy( m43.m_Xy ), m_Xz( m43.m_Xz ),
	  m_Yx( m43.m_Yx ), m_Yy( m43.m_Yy ), m_Yz( m43.m_Yz ),
	  m_Zx( m43.m_Zx ), m_Zy( m43.m_Zy ), m_Zz( m43.m_Zz )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! This function contructs a 3x3 matrix by extracting it from the 4x4 matrix.

Matrix33::Matrix33( Matrix44 const & m44 )
	: m_Xx( m44.m_Xx ), m_Xy( m44.m_Xy ), m_Xz( m44.m_Xz ),
	  m_Yx( m44.m_Yx ), m_Yy( m44.m_Yy ), m_Yz( m44.m_Yz ),
	  m_Zx( m44.m_Zx ), m_Zy( m44.m_Zy ), m_Zz( m44.m_Zz )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

double Matrix33::Determinant() const
{
	return 	Determinant3( *this );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

bool Matrix33::IsOrthonormal() const
{
	float const	r0	= 1.f - sqrtf( m_Xx*m_Xx + m_Xy*m_Xy + m_Xz*m_Xz );
	float const	r1	= 1.f - sqrtf( m_Yx*m_Yx + m_Yy*m_Yy + m_Yz*m_Yz );
	float const	r2	= 1.f - sqrtf( m_Zx*m_Zx + m_Zy*m_Zy + m_Zz*m_Zz );
	float const	c0	= 1.f - sqrtf( m_Xx*m_Xx + m_Yx*m_Yx + m_Zx*m_Zx );
	float const	c1	= 1.f - sqrtf( m_Xy*m_Xy + m_Yy*m_Yy + m_Zy*m_Zy );
	float const	c2	= 1.f - sqrtf( m_Xz*m_Xz + m_Yz*m_Yz + m_Zz*m_Zz );

	return ( ( r0*r0 + r1*r1 + r2*r2 + c0*c0 + c1*c1 + c2*c2 ) < Math::DEFAULT_FLOAT_ORTHONORMAL_TOLERANCE );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33 & Matrix33::Transpose()
{
	swap( m_Xy, m_Yx );
	swap( m_Xz, m_Zx );
	swap( m_Yz, m_Zy );

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33 & Matrix33::Invert()
{
	Matrix33 const	a( *this );
	double const	det	= a.Determinant();

	assert( !Math::IsCloseToZero( det, Math::DEFAULT_DOUBLE_TOLERANCE ) );

	if ( !Math::IsCloseToZero( det, Math::DEFAULT_DOUBLE_TOLERANCE ) )
	{
		m_Xx = float(  Determinant2( a, 1, 2, 1, 2 ) / det );
		m_Xy = float( -Determinant2( a, 0, 2, 1, 2 ) / det );
		m_Xz = float(  Determinant2( a, 0, 1, 1, 2 ) / det );

		m_Yx = float( -Determinant2( a, 1, 2, 0, 2 ) / det );
		m_Yy = float(  Determinant2( a, 0, 2, 0, 2 ) / det );
		m_Yz = float( -Determinant2( a, 0, 1, 0, 2 ) / det );

		m_Zx = float(  Determinant2( a, 1, 2, 0, 1 ) / det );
		m_Zy = float( -Determinant2( a, 0, 2, 0, 1 ) / det );
		m_Zz = float(  Determinant2( a, 0, 1, 0, 1 ) / det );
	}
	else
	{
		*this = Matrix33::Identity();
	}

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33 & Matrix33::PostConcatenate( Matrix33 const & b )
{
	Matrix33	c;

	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			c.m_M[ i ][ j ] =	  m_M[ i ][ 0 ] * b.m_M[ 0 ][ j ]
								+ m_M[ i ][ 1 ] * b.m_M[ 1 ][ j ]
								+ m_M[ i ][ 2 ] * b.m_M[ 2 ][ j ];
		}
	}

	memcpy( m_M, c.m_M, sizeof( m_M ) );

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

Matrix33 & Matrix33::PreConcatenate( Matrix33 const & b )
{
	Matrix33	c;

	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			c.m_M[ i ][ j ] = 	  b.m_M[ i ][ 0 ] * m_M[ 0 ][ j ]
							  	+ b.m_M[ i ][ 1 ] * m_M[ 1 ][ j ]
							  	+ b.m_M[ i ][ 2 ] * m_M[ 2 ][ j ];
		}
	}

	memcpy( m_M, c.m_M, sizeof( m_M ) );

	return *this;
}
