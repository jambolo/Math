/** @file *//********************************************************************************************************

                                                      Vector3.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector3.h#16 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once

#include <iosfwd>

class Matrix33;
class Matrix43;
class Quaternion;

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 3D vector of floats.
//
//! @ingroup Vectors
//!

class Vector3
{
public:

	//! Constructor
	Vector3() {}

	//! Constructor
	Vector3( float x, float y, float z );

	//! Constructor
	Vector3( float const v[ 3 ] );

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
	Vector3 const &	Negate();

	//! Normalizes the vector. Returns the result.
	Vector3 const &	Normalize();

	//! Adds a vector. Returns the result.
	Vector3 const &	Add( Vector3 const & b );

	//! Subtracts a vector. Returns the result.
	Vector3 const &	Subtract( Vector3 const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector3 const &	Scale( float scale );

	//! Transforms the vector (vM). Returns the result.
	Vector3 const &	Transform( Matrix43 const & m );

	//! Transforms the vector (vM). Returns the result.
	Vector3 const &	Transform( Matrix33 const & m );

	//! Rotates the vector around an axis. Returns the result.
	Vector3 const &	Rotate( Vector3 const & axis, float angle );

	//! Rotates the vector.
	Vector3 const &	Rotate( Quaternion const & q );

	//! Adds a vector. Returns the result.
	Vector3 const &	operator +=( Vector3 const & b );

	//! Subtracts a vector. Returns the result.
	Vector3 const &	operator -=( Vector3 const & b );

	//! Scales the vector. Returns the result.
	Vector3 const &	operator *=( float scale );

	//! Transforms the vector (vM). Returns the result.
	Vector3 const &	operator *=( Matrix43 const & m );

	//! Transforms the vector (vM). Returns the result.
	Vector3 const &	operator *=( Matrix33 const & m );

	//! Returns the negative.
	Vector3			operator -()						const;

	union
	{
		float	m_V[ 3 ];	//!< Elements as an array {x, y, z}
		struct
		{
			float	/** */m_X, m_Y, m_Z;
		};
	};

	// Useful constants

	//! Returns [0, 0, 0].
	static Vector3	Origin();

	//! Returns [1, 0, 0].
	static Vector3	XAxis();

	//! Returns [0, 1, 0].
	static Vector3	YAxis();

	//! Returns [0, 0, 1].
	static Vector3	ZAxis();
};

#pragma warning( pop )

//! @name Vector3 Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector3	operator +( Vector3 const & a, Vector3 const & b );

//! Returns the difference between @a a and @a b.
Vector3	operator -( Vector3 const & a, Vector3 const & b );

//! Returns the result of transforming @a v by @a m.
Vector3	operator *( Vector3 const & v, Matrix43 const & m );

//! Returns the result of transforming @a v by @a m.
Vector3	operator *( Matrix43 const & m, Vector3 const & v );

//! Returns the result of transforming @a v by @a m.
Vector3	operator *( Vector3 const & v, Matrix33 const & m );

//! Returns the result of transforming @a v by @a m.
Vector3	operator *( Matrix33 const & m, Vector3 const & v );

//! Returns the dot product of @a a and @a b.
float	Dot( Vector3 const & a, Vector3 const & b );

//! Returns the cross product of @a a and @a b.
Vector3	Cross( Vector3 const & a, Vector3 const & b );

//! Returns the result of scaling @a v by @a s.
Vector3	operator *( Vector3 const & v, float s );

//! Returns the result of scaling @a v by @a s.
Vector3	operator *( float s, Vector3 const & v );

//@}


//! @name Vector3 Insert/Extract Operators
//! @ingroup Vectors
//@{

//! Extracts a Vector3 from a stream
std::istream & operator >>( std::istream & in, Vector3 & v );


//! Inserts a Vector3 into a stream
std::ostream & operator <<( std::ostream & out, Vector3 const & v );

//@}

// Inline functions

#include "Vector3.inl"
