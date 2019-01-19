/** @file *//********************************************************************************************************

                                                      Matrix44d.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix44d.h#10 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Vector3d.h"

class Vector4d;
class Matrix33d;
class Matrix43d;
class Matrix44;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 4x4 matrix of doubles.
//
//! @ingroup Matrices
//!

class Matrix44d
{
public:

	//! Constructor
	Matrix44d() {}

	//! Constructor
	Matrix44d( double Xx, double Xy, double Xz, double Xw,
			   double Yx, double Yy, double Yz, double Yw,
			   double Zx, double Zy, double Zz, double Zw,
			   double Tx, double Ty, double Tz, double Tw );

	//! Constructor
	Matrix44d( Vector3d const & x, Vector3d const & y, Vector3d const & z, Vector3d const & t = Vector3d::Origin() );

	//! Constructor
	explicit Matrix44d( double const * pM );

	//! Constructor
	Matrix44d( Matrix33d const & m33, Vector3d const & t = Vector3d::Origin() );

	//! Conversion
	explicit Matrix44d( Matrix43d const & m43 );

	//! Conversion
	explicit Matrix44d( Matrix44 const & m44 );
	
	//! Returns the X vector.
	Vector4d const &	GetX() 								const;

	//! Returns the Y vector.
	Vector4d const &	GetY() 								const;

	//! Returns the Z vector.
	Vector4d const &	GetZ() 								const;

	//! Returns the T (or W) vector.
	Vector4d const &	GetT() 								const;

	//! Returns the determinant.
	double				Determinant()						const;

	//! Returns true if the matrix is orthonormal (within a tolerance)
	bool				IsOrthonormal()						const;

	//! Transposes the matrix. Returns the result.
	Matrix44d &			Transpose();

	//! Inverts the matrix. Returns the result.
	Matrix44d &			Invert();

	//! Pre-concatenates a matrix. Returns the result.
	Matrix44d &			PreConcatenate( Matrix44d const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix44d &			PostConcatenate( Matrix44d const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix44d &			operator *=( Matrix44d const & b );

	//! Returns the inverse.
	Matrix44d			operator ~()						const;

	//! Matrix elements individually or as an array
	union
	{
		double		m_M[ 4 ][ 4 ];				//!< Elements as a 4x4 array

		//! Individual matrix elements
		struct
		{
			double	/** */m_Xx, m_Xy, m_Xz, m_Xw;
			double	/** */m_Yx, m_Yy, m_Yz, m_Yw;
			double	/** */m_Zx, m_Zy, m_Zz, m_Zw;
			double	/** */m_Tx, m_Ty, m_Tz, m_Tw;
		};
	};

	//! Returns the identity matrix.
	static Matrix44d	Identity();
};

#pragma warning( pop )

// Inline functions

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
