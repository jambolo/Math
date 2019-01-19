/** @file *//********************************************************************************************************

                                                      Vector2.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector2.h#13 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


class Matrix22;

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 2D vector of floats.
//
//! @ingroup Vectors
//!

class Vector2
{
public:

	//! Constructor
	Vector2() {}

	//! Constructor
	Vector2( float x, float y );

	//! Constructor
	Vector2( float const v[ 2 ] );

	//! Returns the length of the vector squared.
	float			Length2()							const;

	//! Returns the length of the vector.
	float			Length()							const;

	//! Returns the inverse of the length of the vector (or 1 if the length is 0).
	float			ILength()							const;

	//! Returns the inverse of the length squared of the vector (or 1 if the length is 0).
	float			ILength2()							const;

	//! Returns true if the vector is normalized (within a tolerance).
	bool			IsNormalized()						const;

	//! Negates the vector. Returns the result.
	Vector2 const &	Negate();

	//! Normalizes the vector. Returns the result.
	Vector2 const &	Normalize();

	//! Adds a vector. Returns the result.
	Vector2 const &	Add( Vector2 const & b );

	//! Subtracts a vector. Returns the result.
	Vector2 const &	Subtract( Vector2 const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector2 const &	Scale( float scale );

	//! Transforms the vector (vM). Returns the result.
	Vector2 const &	Transform( Matrix22 const & m );

	//! Rotates the vector. Returns the result.
	Vector2 const &	Rotate( float angle );

	//! Adds a vector. Returns the result.
	Vector2 const &	operator +=( Vector2 const & b );

	//! Subtracts a vector. Returns the result.
	Vector2 const &	operator -=( Vector2 const & b );

	//! Scales the vector. Returns the result.
	Vector2 const &	operator *=( float scale );

	//! Transforms the vector (vM). Returns the result.
	Vector2 const &	operator *=( Matrix22 const & m );

	//! Returns the negative.
	Vector2			operator -()						const;

	union
	{
		float	m_V[ 2 ];	//!< Elements as an array {x, y}
		struct
		{
			float	/** */m_X, m_Y;
		};
	};

	// Useful constants

	//! Returns [0, 0].
	static Vector2	Origin();

	//! Returns [1, 0].
	static Vector2	XAxis();

	//! Returns [0, 1].
	static Vector2	YAxis();
};

#pragma warning( pop )

//! @name Vector2 Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector2	operator +( Vector2 const & a, Vector2 const & b );

//! Returns the difference between @a a and @a b.
Vector2	operator -( Vector2 const & a, Vector2 const & b );

//! Returns the result of transforming @a v by @a m.
Vector2	operator *( Vector2 const & v, Matrix22 const & m );

//! Returns the result of transforming @a v by @a m.
Vector2	operator *( Matrix22 const & m, Vector2 const & v );

//! Returns the dot product of @a a and @a b.
float	Dot( Vector2 const & a, Vector2 const & b );

//! Returns the result of scaling @a v by @a s.
Vector2	operator *( Vector2 const & v, float s );

//! Returns the result of scaling @a v by @a s.
Vector2	operator *( float s, Vector2 const & v );

//@}

// Inline functions

#include "Vector2.inl"
