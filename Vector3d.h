/** @file *//********************************************************************************************************

                                                      Vector3d.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector3d.h#9 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once



class Matrix33d;
class Matrix43d;
class Quaternion;

/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

#pragma warning( push )
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union

//! A 3D vector of doubles.
//
//! @ingroup Vectors
//!

class Vector3d
{
public:

	//! Constructor
	Vector3d() {}

	//! Constructor
	Vector3d( double x, double y, double z );

	//! Constructor
	Vector3d( double const v[ 3 ] );

	//! Returns the length of the vector squared.
	double				Length2()							const;

	//! Returns the length of the vector.
	double				Length()							const;

	//! Returns the inverse of the length of the vector (or 1. if the length is 0)
	double				ILength()							const;

	//! Returns the inverse of the length squared of the vector (or 1. if the length is 0)
	double				ILength2()							const;

	//! Returns true if the vector is normalized (within a tolerance).
	bool				IsNormalized()						const;

	//! Negates the vector. Returns the result.
	Vector3d const &	Negate();

	//! Normalizes the vector. Returns the result.
	Vector3d const &	Normalize();

	//! Adds a vector. Returns the result.
	Vector3d const &	Add( Vector3d const & b );

	//! Subtracts a vector. Returns the result.
	Vector3d const &	Subtract( Vector3d const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector3d const &	Scale( double scale );

	//! Transforms the vector (vM). Returns the result.
	Vector3d const &	Transform( Matrix43d const & m );

	//! Transforms the vector (vM). Returns the result.
	Vector3d const &	Transform( Matrix33d const & m );

	//! Rotates the vector around an axis. Returns the result.
	Vector3d const &	Rotate( Vector3d const & axis, double angle );

	//! Rotates the vector. Returns the result.
	Vector3d const &	Rotate( Quaternion const & q );

	//! Adds a vector. Returns the result.
	Vector3d const &	operator +=( Vector3d const & b );

	//! Subtracts a vector. Returns the result.
	Vector3d const &	operator -=( Vector3d const & b );

	//! Multiplies the vector by a scalar. Returns the result.
	Vector3d const &	operator *=( double scale );

	//! Transforms the vector (vM). Returns the result.
	Vector3d const &	operator *=( Matrix43d const & m );

	//! Transforms the vector (vM). Returns the result.
	Vector3d const &	operator *=( Matrix33d const & m );

	//! Returns the negative.
	Vector3d			operator -()						const;

	union
	{
		double	m_V[ 3 ];	//!< Elements as an array {x, y, z}
		struct
		{
			double	/** */m_X, m_Y, m_Z;
		};
	};

	// Useful constants

	//! Returns [0, 0, 0].
	static Vector3d	Origin();

	//! Returns [1, 0, 0].
	static Vector3d	XAxis();

	//! Returns [0, 1, 0].
	static Vector3d	YAxis();

	//! Returns [0, 0, 1].
	static Vector3d	ZAxis();
};

#pragma warning( pop )

//! @name Vector3d Binary Operators
//! @ingroup Vectors
//@{

//! Returns the sum of @a a and @a b.
Vector3d operator +( Vector3d const & a, Vector3d const & b );

//! Returns the difference between @a a and @a b.
Vector3d operator -( Vector3d const & a, Vector3d const & b );

//! Returns the result of transforming @a v by @a m.
Vector3d operator *( Vector3d const & v, Matrix43d const & m );

//! Returns the result of transforming @a v by @a m.
Vector3d operator *( Matrix43d const & m, Vector3d const & v );

//! Returns the result of transforming @a v by @a m.
Vector3d operator *( Vector3d const & v, Matrix33d const & m );

//! Returns the result of transforming @a v by @a m.
Vector3d operator *( Matrix33d const & m, Vector3d const & v );

//! Returns the dot product of @a a and @a b.
double Dot( Vector3d const & a, Vector3d const & b );

//! Returns the cross product of @a a and @a b.
Vector3d Cross( Vector3d const & a, Vector3d const & b );

//! Returns the result of scaling @a v by @a s.
Vector3d operator *( Vector3d const & v, double s );

//! Returns the result of scaling @a v by @a s.
Vector3d operator *( double s, Vector3d const & v );

//@}

// Inline functions

#include "Vector3d.inl"
