/** @file *//********************************************************************************************************

                                                     Matrix44.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix44.h#14 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Vector3.h"

class Matrix33;
class Matrix43;
class Matrix44d;
class Vector4;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 4x4 matrix of floats.
//
//! @ingroup Matrices
//!

class Matrix44
{
public:

	//! Constructor
	Matrix44() {}

	//! Constructor
	Matrix44( float Xx, float Xy, float Xz, float Xw,
			  float Yx, float Yy, float Yz, float Yw,
			  float Zx, float Zy, float Zz, float Zw,
			  float Tx, float Ty, float Tz, float Tw );

	//! Constructor
	Matrix44( Vector3 const & x,
			  Vector3 const & y,
			  Vector3 const & z,
			  Vector3 const & t = Vector3::Origin() );

	//! Constructor
	explicit Matrix44( float const * pM );

	//! Constructor
	Matrix44( Matrix33 const & m33, Vector3 const & t = Vector3::Origin() );

	//! Conversion
	explicit Matrix44( Matrix43 const & m43 );

	//! Conversion
	explicit Matrix44( Matrix44d const & m44d );

	//! Returns the X vector.
	Vector4 const &	GetX() 								const;

	//! Returns the Y vector.
	Vector4 const &	GetY() 								const;

	//! Returns the Z vector.
	Vector4 const &	GetZ() 								const;

	//! Returns the T (or W) vector.
	Vector4 const &	GetT() 								const;

	//! Returns the determinant.
	double			Determinant()						const;

	//! Returns true if the matrix is orthonormal (within a tolerance)
	bool			IsOrthonormal()						const;

	//! Transposes the matrix. Returns the result.
	Matrix44 &		Transpose();

	//! Inverts the matrix. Returns the result.
	Matrix44 &		Invert();

	//! Pre-concatenates a matrix. Returns the result.
	Matrix44 &		PreConcatenate( Matrix44 const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix44 &		PostConcatenate( Matrix44 const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix44 &		operator *=( Matrix44 const & b );

	//! Returns the inverse.
	Matrix44		operator ~()						const;

	union
	{
		float		m_M[ 4 ][ 4 ];	//!< Elements as a 4x4 array
		struct
		{
			//! @name	Matrix elements
			//@{
			float	/** */m_Xx, /** */m_Xy, /** */m_Xz, /** */m_Xw;
			float	/** */m_Yx, /** */m_Yy, /** */m_Yz, /** */m_Yw;
			float	/** */m_Zx, /** */m_Zy, /** */m_Zz, /** */m_Zw;
			float	/** */m_Tx, /** */m_Ty, /** */m_Tz, /** */m_Tw;
			//@}
		};
	};

	//! Returns the identity matrix.
	static Matrix44	Identity();
};

#pragma warning( pop )

// Inline functions

#include "Matrix44.inl"
