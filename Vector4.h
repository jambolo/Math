/** @file *//********************************************************************************************************

                                                      Vector4.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector4.h#13 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


class Matrix43;
class Matrix44;
class Quaternion;


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 4D vector of floats.
//
//! @ingroup Vectors
//!

class Vector4
{
public:
	
	//! Constructor
	Vector4() {}

	//! Constructor
	Vector4( float x, float y, float z, float w );

	//! Constructor
	Vector4( float const v[ 4 ] );

	//! Returns the length of the vector squared.
	float				Length2()							const;

	//! Returns the length of the vector.
	float				Length()							const;

	//! Returns the inverse of the length of the vector (or 1 if the length is 0)
	float				ILength()							const;

	//! Returns the inverse of the length squared of the vector (or 1 if the length is 0)
	float				ILength2()							const;

	//! Returns true if the vector is normalized (within a tolerance).
	bool				IsNormalized()						const;

	//! Negates the vector. Returns the result.
	Vector4 const &	Negate();

	//! Normalizes the vector. Returns the result.
	Vector4 const &	Normalize();

	//! Adds a vector. Returns the result.
	Vector4 const &	Add( Vector4 const & b );

	//! Subtracts a vector. Returns the result.
	Vector4 const &	Subtract( Vector4 const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector4 const &	Scale( float scale );

	//! Transforms the vector. Returns the result.
	Vector4 const &	Transform( Matrix43 const & m );

	//! Transforms the vector. Returns the result
	Vector4 const &	Transform( Matrix44 const & m );

	//! Rotates the vector around an axis. Returns the result.
	Vector4 const &	Rotate( Vector4 const & axis, float angle );

	//! Rotates the vector
	Vector4 const &	Rotate( Quaternion const & q );

	//! Adds a vector. Returns the result.
	Vector4 const &	operator +=( Vector4 const & b );

	//! Subtracts a vector. Returns the result.
	Vector4 const &	operator -=( Vector4 const & b );

	//! Scales the vector. Returns the result.
	Vector4 const &	operator *=( float scale );

	//! Transforms the vector. Returns the result.
	Vector4 const &	operator *=( Matrix43 const & m );

	//! Transforms the vector. Returns the result.
	Vector4 const &	operator *=( Matrix44 const & m );

	//! Returns the negative.
	Vector4			operator -()							const;

	union
	{
		float	m_V[ 4 ];	//!< Elements as an array {x, y, z, w}
		struct
		{
			float	/** */m_X, m_Y, m_Z, m_W;
		};
	};

	// Useful constants

	//! Returns [0, 0, 0, 0].
	static Vector4	Origin();

	//! Returns [1, 0, 0, 0].
	static Vector4	XAxis();

	//! Returns [0, 1, 0, 0].
	static Vector4	YAxis();

	//! Returns [0, 0, 1, 0].
	static Vector4	ZAxis();

	//! Returns [0, 0, 0, 1].
	static Vector4	WAxis();
};

#pragma warning( pop )

//! @name Vector4 Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector4 operator +( Vector4 const & a, Vector4 const & b );

//! Returns the difference between @a a and @a b.
Vector4 operator -( Vector4 const & a, Vector4 const & b );

//! Returns the result of transforming @a v by @a m.
Vector4 operator *( Vector4 const & v, Matrix43 const & m );

//! Returns the result of transforming @a v by @a m.
Vector4 operator *( Matrix43 const & m, Vector4 const & v );

//! Returns the result of transforming @a v by @a m.
Vector4 operator *( Vector4 const & v, Matrix44 const & m );

//! Returns the result of transforming @a v by @a m.
Vector4 operator *( Matrix44 const & m, Vector4 const & v );

//! Returns the dot product of @a a and @a b.
float	Dot( Vector4 const & a, Vector4 const & b );

//! Returns the result of scaling @a v by @a s.
Vector4	operator *( Vector4 const & v, float s );

//! Returns the result of scaling @a v by @a s.
Vector4	operator *( float s, Vector4 const & v );

//@}

// Inline functions

#include "Vector4.inl"
