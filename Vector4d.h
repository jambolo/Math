/** @file *//********************************************************************************************************

                                                      Vector4d.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector4d.h#9 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once



class Matrix43d;
class Matrix44d;
class Quaternion;

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 4D vector of doubles.
//
//! @ingroup Vectors
//!

class Vector4d
{
public:

	//! Constructor
	Vector4d() {}

	//! Constructor
	Vector4d( double x, double y, double z, double w );

	//! Constructor
	Vector4d( double const v[ 4 ] );

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
	Vector4d const &	Negate();

	//! Normalizes the vector. Returns the result.
	Vector4d const &	Normalize();

	//! Adds a vector. Returns the result.
	Vector4d const &	Add( Vector4d const & b );

	//! Subtracts a vector. Returns the result.
	Vector4d const &	Subtract( Vector4d const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector4d const &	Scale( double scale );

	//! Transforms the vector (vM). Returns the result.
	Vector4d const &	Transform( Matrix43d const & m );

	//! Transforms the vector (vM). Returns the result.
	Vector4d const &	Transform( Matrix44d const & m );

	//! Rotates the vector around an axis. Returns the result.
	Vector4d const &	Rotate( Vector4d const & axis, double angle );

	//! Rotates the vector. Returns the result.
	Vector4d const &	Rotate( Quaternion const & q );

	//! Adds a vector. Returns the result.
	Vector4d const &	operator +=( Vector4d const & b );

	//! Subtracts a vector. Returns the result.
	Vector4d const &	operator -=( Vector4d const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector4d const &	operator *=( double scale );

	//! Transforms the vector. Returns the result.
	Vector4d const &	operator *=( Matrix43d const & m );

	//! Transforms the vector. Returns the result.
	Vector4d const &	operator *=( Matrix44d const & m );

	//! Returns the negative.
	Vector4d			operator -()						const;

	union
	{
		double	m_V[ 4 ];	//!< Elements as an array {x, y, z, w}
		struct
		{
			double	/** */m_X, m_Y, m_Z, m_W;
		};
	};

	// Useful constants

	//! Returns [0, 0, 0, 0].
	static Vector4d	Origin();

	//! Returns [1, 0, 0, 0].
	static Vector4d	XAxis();

	//! Returns [0, 1, 0, 0].
	static Vector4d	YAxis();

	//! Returns [0, 0, 1, 0].
	static Vector4d	ZAxis();

	//! Returns [0, 0, 0, 1].
	static Vector4d	WAxis();
};

#pragma warning( pop )

//! @name Vector4d Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector4d operator +( Vector4d const & a, Vector4d const & b );

//! Returns the difference between @a a and @a b.
Vector4d operator -( Vector4d const & a, Vector4d const & b );

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *( Vector4d const & v, Matrix43d const & m );

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *( Matrix43d const & m, Vector4d const & v );

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *( Vector4d const & v, Matrix44d const & m );

//! Returns the result of transforming the vector @a v by @a m.
Vector4d operator *( Matrix44d const & m, Vector4d const & v );

//! Returns the dot product of a and b.
double Dot( Vector4d const & a, Vector4d const & b );

//! Returns the result of scaling v by s.
Vector4d operator *( Vector4d const & v, double s );

//! Returns the result of scaling v by s.
Vector4d operator *( double s, Vector4d const & v );

//@}

// Inline functions

#include "Vector4d.inl"
