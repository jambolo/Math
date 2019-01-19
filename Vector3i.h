/** @file *//********************************************************************************************************

                                                      Vector3i.h

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector3i.h#6 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include <iosfwd>

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 3D vector of integers.
//
//! @ingroup Vectors
//!

class Vector3i
{
public:

	//! Constructor
	Vector3i() {}

	//! Constructor
	Vector3i( int x, int y, int z );

	//! Constructor
	Vector3i( int const v[ 3 ] );

	//! Negates the vector. Returns the result.
	Vector3i const &	Negate();

	//! Adds a vector. Returns the result.
	Vector3i const &	Add( Vector3i const & b );

	//! Subtracts a vector. Returns the result.
	Vector3i const &	Subtract( Vector3i const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector3i const &	Scale( int scale );

	//! Adds a vector. Returns the result.
	Vector3i const &	operator +=( Vector3i const & b );

	//! Subtracts a vector. Returns the result.
	Vector3i const &	operator -=( Vector3i const & b );

	//! Scales the vector. Returns the result.
	Vector3i const &	operator *=( int scale );

	//! Returns the negative.
	Vector3i			operator -()							const;

	//! Returns the sum.
	Vector3i			operator +( Vector3i const & b )		const;

	//! Returns the difference.
	Vector3i			operator -( Vector3i const & b )		const;

	union
	{
		int	m_V[ 3 ];	//!< Elements as an array {x, y, z}
		struct
		{
			int	/** */m_X, m_Y, m_Z;
		};
	};

	// Useful constants

	//! Returns [0, 0, 0].
	static Vector3i	Origin();

	//! Returns [1, 0, 0].
	static Vector3i	XAxis();

	//! Returns [0, 1, 0].
	static Vector3i	YAxis();

	//! Returns [0, 0, 1].
	static Vector3i	ZAxis();
};

#pragma warning( pop )

//! @name Vector3i Binary Operators
//! @ingroup Vectors
//@{

//! Returns the result of scaling v by s.
Vector3i	operator *( Vector3i const & v, int s );

//! Returns the result of scaling v by s.
Vector3i	operator *( int s, Vector3i const & v );

//@}

//! @name Vector3i Insert/Extract Operators
//! @ingroup Vectors
//@{

//! Extracts a Vector3i from a stream
std::istream & operator >>( std::istream & in, Vector3i & v );


//! Inserts a Vector3i into a stream
std::ostream & operator <<( std::ostream & out, Vector3i const & v );

//@}

// Inline functions

#include "Vector3i.inl"
