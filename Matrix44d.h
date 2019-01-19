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

#include "Matrix44d.inl"
