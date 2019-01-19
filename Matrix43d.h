/** @file *//********************************************************************************************************

                                                      Matrix43d.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Matrix43d.h#10 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Vector3d.h"

class Matrix33d;
class Matrix43;
class Matrix44d;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 4x3 matrix of doubles.
//
//! @ingroup Matrices
//!

class Matrix43d
{
public:

	//! Constructor
	Matrix43d() {}

	//! Constructor
	Matrix43d( double Xx, double Xy, double Xz,
			   double Yx, double Yy, double Yz,
			   double Zx, double Zy, double Zz,
			   double Tx, double Ty, double Tz );

	//! Constructor
	Matrix43d( Vector3d const & x, Vector3d const & y, Vector3d const & z, Vector3d const & t = Vector3d::Origin() );

	//! Constructor
	explicit Matrix43d( double const * pM );

	//! Constructor
	Matrix43d( Matrix33d const & m33, Vector3d const & t = Vector3d::Origin() );

	//! Conversion
	explicit Matrix43d( Matrix43 const & m43 );

	//! Conversion
	explicit Matrix43d( Matrix44d const & m44 );
	
	//! Returns the X vector.
	Vector3d const &	GetX() 									const;

	//! Returns the Y vector.
	Vector3d const &	GetY() 									const;

	//! Returns the Z vector.
	Vector3d const &	GetZ() 									const;

	//! Returns the T vector.
	Vector3d const &	GetT() 									const;

	//! Returns the determinant.
	double				Determinant()							const;

	//! Returns true if the matrix is orthonormal (within a tolerance)
	bool				IsOrthonormal()							const;

	//! Inverts the matrix. Returns the result.
	Matrix43d &			Invert();

	//! Pre-concatenates a matrix returns the result.
	Matrix43d &			PreConcatenate( Matrix43d const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix43d &			PostConcatenate( Matrix43d const & b );

	//! Post-concatenates a matrix. Returns the result.
	Matrix43d &			operator *=( Matrix43d const & b );

	//! Returns the inverse.
	Matrix43d			operator ~()							const;

	union
	{
		double		m_M[ 4 ][ 3 ];			//!< Elements as a 4x3 row-major array
		struct
		{
			//! @name	Matrix elements
			//@{
			double	/** */m_Xx, /** */m_Xy, /** */m_Xz;
			double	/** */m_Yx, /** */m_Yy, /** */m_Yz;
			double	/** */m_Zx, /** */m_Zy, /** */m_Zz;
			double	/** */m_Tx, /** */m_Ty, /** */m_Tz;
			//@}
		};
	};

	//! Returns the identity matrix.
	static Matrix43d	Identity();
};

#pragma warning( pop )


// Inline functions

#include "Matrix43d.inl"
