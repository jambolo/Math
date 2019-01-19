/** @file *//********************************************************************************************************

                                                      Vector2i.h

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector2i.h#4 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 2D vector of integers.
//
//! @ingroup Vectors
//!

class Vector2i
{
public:

	//! Constructor
	Vector2i() {}

	//! Constructor
	Vector2i( int x, int y );

	//! Constructor
	Vector2i( int const v[ 2 ] );

	//! Negates the vector. Returns the result.
	Vector2i const &	Negate();

	//! Adds a vector. Returns the result.
	Vector2i const &	Add( Vector2i const & b );

	//! Subtracts a vector. Returns the result.
	Vector2i const &	Subtract( Vector2i const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector2i const &	Scale( int scale );

	//! Adds a vector. Returns the result.
	Vector2i const &	operator +=( Vector2i const & b );

	//! Subtracts a vector. Returns the result.
	Vector2i const &	operator -=( Vector2i const & b );

	//! Scales the vector. Returns the result.
	Vector2i const &	operator *=( int scale );

	//! Returns the negative.
	Vector2i			operator -()						const;

	union
	{
		int	m_V[ 2 ];	//!< Elements as an array {x, y}
		struct
		{
			int	/** */m_X, m_Y;
		};
	};

	// Useful constants

	//! Returns [0, 0].
	static Vector2i	Origin();

	//! Returns [1, 0].
	static Vector2i	XAxis();

	//! Returns [0, 1].
	static Vector2i	YAxis();
};

#pragma warning( pop )

//! @name Vector2i Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector2i	operator +( Vector2i const & a, Vector2i const & b );

//! Returns the difference between @a a and @a b.
Vector2i	operator -( Vector2i const & a, Vector2i const & b );

//! Returns the result of scaling @a v by @a s.
Vector2i	operator *( Vector2i const & v, int s );

//! Returns the result of scaling @a v by @a s.
Vector2i	operator *( int s, Vector2i const & v );

//@}

//! @name Vector3i Insert/Extract Operators
//! @ingroup Vectors
//@{

//! Extracts a Vector3i from a stream
std::istream & operator >>( std::istream & in, Vector2i & v );


//! Inserts a Vector3i into a stream
std::ostream & operator <<( std::ostream & out, Vector2i const & v );

//@}

// Inline functions

#include "Vector2i.inl"
