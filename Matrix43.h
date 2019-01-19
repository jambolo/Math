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

#include "Matrix43.inl"
