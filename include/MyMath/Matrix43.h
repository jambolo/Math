/** @file *//********************************************************************************************************

                                                     Matrix43.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix43.h#14 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Vector3.h"

class Matrix33;
class Matrix43d;
class Matrix44;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 4x3 matrix of floats (4 3-element basis vectors)
//
//! @ingroup Matrices
//!

class Matrix43
{
public:

	//! Constructor
	Matrix43() {}

	//! Constructor
	Matrix43( float Xx, float Xy, float Xz,
			  float Yx, float Yy, float Yz,
			  float Zx, float Zy, float Zz,
			  float Tx, float Ty, float Tz );

	//! Constructor
	Matrix43( Vector3 const & x,
			  Vector3 const & y,
			  Vector3 const & z,
			  Vector3 const & t = Vector3::Origin() );

	//! Constructor
	explicit Matrix43( float const * pM );

	//! Constructor
	Matrix43( Matrix33 const & m33, Vector3 const & t = Vector3::Origin() );

	//! Conversion
	explicit Matrix43( Matrix43d const & m43d );

	//! Conversion
	explicit Matrix43( Matrix44 const & m44 );
	
	//! Returns the X vector.
	Vector3 const &	GetX() 									const;

	//! Returns the Y vector.
	Vector3 const &	GetY() 									const;

	//! Returns the Z vector.
	Vector3 const &	GetZ() 									const;

	//! Returns the T vector.
	Vector3 const &	GetT() 									const;

	//! Returns the determinant.
	double			Determinant()							const;

	//! Returns true if the matrix is orthonormal (within a tolerance)
	bool			IsOrthonormal()							const;

	//! Inverts the matrix. Returns the result.
	Matrix43 &		Invert();

	//! Pre-concatenates a matrix. Returns the result.
	Matrix43 &		PreConcatenate( Matrix43 const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix43 &		PostConcatenate( Matrix43 const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix43 &		operator *=( Matrix43 const & b );

	//! Returns the inverse.
	Matrix43		operator ~()							const;

	union
	{
		float		m_M[ 4 ][ 3 ];			//!< Elements as a 4x3 row-major array.
		struct
		{
			//! @name	Matrix elements
			//@{
			float	/** */m_Xx, /** */m_Xy, /** */m_Xz;
			float	/** */m_Yx, /** */m_Yy, /** */m_Yz;
			float	/** */m_Zx, /** */m_Zy, /** */m_Zz;
			float	/** */m_Tx, /** */m_Ty, /** */m_Tz;
			//@}
		};
	};

	//! Returns the identity matrix.
	static Matrix43	Identity();
};

#pragma warning( pop )

// Inline functions

#include "Vector3.h"


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix43::Matrix43( float Xx, float Xy, float Xz,
						   float Yx, float Yy, float Yz,
						   float Zx, float Zy, float Zz,
						   float Tx, float Ty, float Tz )

	: m_Xx( Xx ), m_Xy( Xy ), m_Xz( Xz ),
	  m_Yx( Yx ), m_Yy( Yy ), m_Yz( Yz ),
	  m_Zx( Zx ), m_Zy( Zy ), m_Zz( Zz ),
	  m_Tx( Tx ), m_Ty( Ty ), m_Tz( Tz )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix43::Matrix43( Vector3 const & x,
						   Vector3 const & y,
						   Vector3 const & z,
						   Vector3 const & t/* = Vector3::Origin()*/ )
	: m_Xx( x.m_X ), m_Xy( x.m_Y ), m_Xz( x.m_Z ),
	  m_Yx( y.m_X ), m_Yy( y.m_Y ), m_Yz( y.m_Z ),
	  m_Zx( z.m_X ), m_Zy( z.m_Y ), m_Zz( z.m_Z ),
	  m_Tx( t.m_X ), m_Ty( t.m_Y ), m_Tz( t.m_Z )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const &	Matrix43::GetX() const
{
	return *reinterpret_cast< Vector3 const * >( &m_Xx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const &	Matrix43::GetY() const
{
	return *reinterpret_cast< Vector3 const * >( &m_Yx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const &	Matrix43::GetZ() const
{
	return *reinterpret_cast< Vector3 const * >( &m_Zx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const &	Matrix43::GetT() const
{
	return *reinterpret_cast< Vector3 const * >( &m_Tx );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix43 & Matrix43::operator *=( Matrix43 const & b )
{
	return PostConcatenate( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline 	Matrix43 Matrix43::operator ~() const
{
	return Matrix43( *this ).Invert();
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Matrix43 Matrix43::Identity()
{
	return Matrix43( 1.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 1.0f,
					 0.0f, 0.0f, 0.0f );
}
