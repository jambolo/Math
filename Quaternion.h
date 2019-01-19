/** @file *//********************************************************************************************************

                                                     Quaternion.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Quaternion.h#12 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include <iosfwd>

class Matrix33;
class Vector3;

//! @defgroup	Quaternions		Quaternions
//!
//@{

/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A quaternion.

class Quaternion
{
public:

	//! Constructor
	Quaternion() {}

	//! Constructor
	Quaternion( float x, float y, float z, float w );

	//! Constructor
	Quaternion( float const q[ 4 ] );

	//! Constructor
	Quaternion( Vector3 const & axis, float angle );

	//! Constructor
	Quaternion( float yaw, float pitch, float roll );

	//! Conversion
	explicit Quaternion( Matrix33 const & m33 );

	//! Returns an equivalent rotation matrix.
	Matrix33 GetRotationMatrix33()									const;

	//! Returns an equivalent rotation axis and angle.
	void GetRotationAxisAndAngle( Vector3 * pAxis, float * pAngle )	const;

	//! Returns the length of the quaternion squared.
	float Length2()													const;

	//! Returns the length of the quaternion.
	float Length()													const;

	//! Returns the inverse of the length of the quaternion (or 1 if the length is 0).
	float ILength()													const;

	//! Returns the inverse of the length squared of the quaternion (or 1 if the length is 0).
	float ILength2()													const;

	//! Returns true if the quaternion is normalized (within a tolerance).
	bool IsNormalized()												const;

	//! Returns the result of raising the quaternion to a power.
	Quaternion Pow( float b )										const;

	//! Normalizes the quaternion. Returns the result.
	Quaternion const & Normalize();

	//! Replaces the quaternion with its conjugate. Returns the result.
	Quaternion const & Conjugate();

	//! Adds a quaternion. Returns the result.
	Quaternion const & Add( Quaternion const & b );

	//! Subtracts a quaternion. Returns the result.
	Quaternion const & Subtract( Quaternion const & b );

	//! Scales the quaternion. Returns the result.
	Quaternion const & Scale( float scale );

	//! Multiplies the quaternion. Returns the result.
	Quaternion const & Multiply( Quaternion const & b );

	//! Adds a quaternion. Returns the result.
	Quaternion const & operator +=( Quaternion const & b );

	//! Subtracts a quaternion. Returns the result.
	Quaternion const & operator -=( Quaternion const & b );

	//! Scales the quaternion. Returns the result.
	Quaternion const & operator *=( float scale );

	//! Multiplies the quaternion by another. Returns the result.
	Quaternion const & operator *=( Quaternion const & b );

	//! Returns the conjugate.
	Quaternion operator -()											const;

	union
	{
		float	m_Q[ 4 ];	//!< Elements as an array {x, y, z, w}
		struct
		{
			float	/** */m_X, m_Y, m_Z, m_W;
		};
	};

	//! Returns the multiplicative identity [0, 0, 0, 1].
	static Quaternion	Identity();
};

#pragma warning( pop )

//! Returns the sum of @a a and @a b.
Quaternion operator +( Quaternion const & a, Quaternion const & b );

//! Returns the difference between @a a and @a b.
Quaternion operator -( Quaternion const & a, Quaternion const & b );

//! Returns the product of @a a and @a b.
Quaternion operator *( Quaternion const & a, Quaternion const & b );

//! Returns the result of scaling @a q by @a scale.
Quaternion operator *( Quaternion const & q, float scale );

//! Returns the result of scaling @a q by @a scale.
Quaternion operator *( float scale, Quaternion const & q );

//! Extracts a Quaternion from a stream
std::istream & operator>>( std::istream & in, Quaternion & q );


//! Inserts a Quaternion into a stream
std::ostream & operator<<( std::ostream & out, Quaternion const & q );

//@}

// Inline functions

#include "Quaternion.inl"
