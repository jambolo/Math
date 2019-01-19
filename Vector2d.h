/** @file *//********************************************************************************************************

                                                      Vector2d.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector2d.h#9 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


class Matrix22d;

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 2D vector of doubles.
//
//! @ingroup Vectors
//!

class Vector2d
{
public:
	
	//! Constructor
	Vector2d() {}

	//! Constructor
	Vector2d( double x, double y );

	//! Constructor
	Vector2d( double const v[ 2 ] );

	//! Returns the length of the vector squared.
	double				Length2()							const;

	//! Returns the length of the vector.
	double				Length()							const;

	//! Returns the inverse of the length of the vector (or 1 if the length is 0)
	double				ILength()							const;

	//! Returns the inverse of the length squared of the vector (or 1 if the length is 0)
	double				ILength2()							const;

	//! Returns true if the vector is normalized (within a tolerance).
	bool				IsNormalized()						const;

	//! Negates the vector. Returns the result.
	Vector2d const &	Negate();

	//! Normalizes the vector. Returns the result.
	Vector2d const &	Normalize();

	//! Adds a vector. Returns the result.
	Vector2d const &	Add( Vector2d const & b );

	//! Subtracts a vector. Returns the result.
	Vector2d const &	Subtract( Vector2d const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector2d const &	Scale( double scale );

	//! Transforms the vector (vM). Returns the result.
	Vector2d const &	Transform( Matrix22d const & m );

	//! Rotates the vector around an axis. Returns the result.
	Vector2d const &	Rotate( double angle );

	//! Adds a vector. Returns the result.
	Vector2d const &	operator +=( Vector2d const & b );

	//! Subtracts a vector. Returns the result.
	Vector2d const &	operator -=( Vector2d const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector2d const &	operator *=( double scale );

	//! Transforms the vector (vM). Returns the result.
	Vector2d const &	operator *=( Matrix22d const & m );

	//! Returns the negative.
	Vector2d			operator -()						const;

	union
	{
		double	m_V[ 2 ];	//!< Elements as an array {x, y}
		struct
		{
			double	/** */m_X, m_Y;
		};
	};

	// Useful constants

	//! Returns [0, 0].
	static Vector2d	Origin();

	//! Returns [1, 0].
	static Vector2d	XAxis();

	//! Returns [0, 1].
	static Vector2d	YAxis();
};

#pragma warning( pop )

//! @name Vector2d Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector2d	operator +( Vector2d const & a, Vector2d const & b );

//! Returns the difference between @a a and @a b.
Vector2d	operator -( Vector2d const & a, Vector2d const & b );

//! Returns the result of transforming @a v by @a m.
Vector2d	operator *( Vector2d const & v, Matrix22d const & m );

//! Returns the result of transforming @a v by @a m.
Vector2d	operator *( Matrix22d const & m, Vector2d const & v );

//! Returns the dot product of @a a and @a b.
double		Dot( Vector2d const & a, Vector2d const & b );

//! Returns the result of scaling @a v by @a s.
Vector2d	operator *( Vector2d const & v, double s );

//! Returns the result of scaling @a v by @a s.
Vector2d	operator *( double s, Vector2d const & v );

//@}

// Inline functions

#include "Vector2d.inl"
