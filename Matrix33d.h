/** @file *//********************************************************************************************************

                                                      Matrix33d.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix33d.h#10 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


class Vector3d;
class Matrix33;
class Matrix43d;
class Matrix44d;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 3x3 matrix of doubles.
//
//! @ingroup Matrices
//!

class Matrix33d
{
public:

	//! Constructor
	Matrix33d() {}

	//! Constructor
	Matrix33d( double xx, double xy, double xz,
			   double yx, double yy, double yz,
			   double zx, double zy, double zz );

	//! Constructor
	Matrix33d( Vector3d const & x, Vector3d const & y, Vector3d const & z );

	//! Constructor
	explicit Matrix33d( double const * pM );

	//! Conversion
	explicit Matrix33d( Matrix33 const & m33 );

	//! Conversion
	explicit Matrix33d( Matrix43d const & m43 );

	//! Conversion
	explicit Matrix33d( Matrix44d const & m44 );

	//! Returns the X vector.
	Vector3d const &	GetX() 									const;

	//! Returns the Y vector.
	Vector3d const &	GetY() 									const;

	//! Returns the Z vector.
	Vector3d const &	GetZ() 									const;

	//! Returns the determinant.
	double				Determinant()							const;

	//! Returns true if the matrix is orthonormal (within a tolerance)
	bool				IsOrthonormal()							const;

	//! Transposes the matrix. Returns the result.
	Matrix33d &			Transpose();

	//! Inverts the matrix. Returns the result.
	Matrix33d &			Invert();

	//! Pre-concatenates a matrix. Returns the result.
	Matrix33d &			PreConcatenate( Matrix33d const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix33d &			PostConcatenate( Matrix33d const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix33d &			operator *=( Matrix33d const & b );

	//! Returns the inverse.
	Matrix33d			operator ~()							const;

	union
	{
		double		m_M[ 3 ][ 3 ];			//!< Elements as a 3x3 row-major array
		struct
		{
			//! @name	Matrix elements
			//@{
			double	/** */m_Xx, /** */m_Xy, /** */m_Xz;
			double	/** */m_Yx, /** */m_Yy, /** */m_Yz;
			double	/** */m_Zx, /** */m_Zy, /** */m_Zz;
			//@}
		};
	};
	
	//! Returns the identity matrix.
	static Matrix33d	Identity();

};

#pragma warning( pop )

// Inline functions

#include "Matrix33d.inl"
