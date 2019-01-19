/** @file *//********************************************************************************************************

                                                     Matrix33.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix33.h#14 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


class Vector3;
class Matrix33d;
class Matrix43;
class Matrix44;



/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 3x3 matrix of floats.
//
//! @ingroup Matrices
//!

class Matrix33
{
public:

	//! Constructor
	Matrix33() {}

	//! Constructor
	Matrix33( float xx, float xy, float xz,
			  float yx, float yy, float yz,
			  float zx, float zy, float zz );

	//! Constructor
	explicit Matrix33( float const * pM );

	//! Constructor
	Matrix33( Vector3 const & x, Vector3 const & y, Vector3 const & z );

	//! Conversion
	explicit Matrix33( Matrix33d const & m33d );

	//! Conversion
	explicit Matrix33( Matrix43 const & m43 );

	//! Conversion
	explicit Matrix33( Matrix44 const & m44 );

	//! Returns the X vector.
	Vector3 const &	GetX() 								const;

	//! Returns the Y vector.
	Vector3 const &	GetY() 								const;

	//! returns the Z vector.
	Vector3 const &	GetZ() 								const;

	//! Returns the determinant.
	double			Determinant()						const;

	//! Returns true if the matrix is orthonormal (within a tolerance)
	bool			IsOrthonormal()						const;

	//! Tranposes the matrix. Returns the result.
	Matrix33 &		Transpose();

	//! Inverts the matrix. Returns the result.
	Matrix33 &		Invert();

	//! Pre-concatenates a matrix. Returns the result.
	Matrix33 &		PreConcatenate( Matrix33 const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix33 &		PostConcatenate( Matrix33 const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix33 &		operator *=( Matrix33 const & b );

	//! Returns the inverse.
	Matrix33		operator ~()						const;

	union
	{
		float		m_M[ 3 ][ 3 ];			//!< Elements as a 3x3 array.
		struct
		{
			//! @name	Matrix elements
			//@{
			float	/** */m_Xx, /** */m_Xy, /** */m_Xz;
			float	/** */m_Yx, /** */m_Yy, /** */m_Yz;
			float	/** */m_Zx, /** */m_Zy, /** */m_Zz;
			//@}
		};
	};

	//! Returns the identity matrix
	static Matrix33	Identity();
};

#pragma warning( pop )

// Inline functions

#include "Matrix33.inl"
