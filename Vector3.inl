/** @file *//********************************************************************************************************

                                                     Vector3.inl

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/Vector3.inl#14 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


#include "Vector3.h"

#include "Math.h"

#include <cassert>
#include <cmath>


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3::Vector3( float x, float y, float z )
	: m_X( x ), m_Y( y ), m_Z( z )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3::Vector3( float const v[ 3 ] )
	: m_X( v[ 0 ] ), m_Y( v[ 1 ] ), m_Z( v[ 2 ] )
{
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline float Vector3::Length2() const
{
//	return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z ); 

	float	len2;

	__asm
	{
		femms
		mov 		eax,this
		movq		mm0,[eax]
		movd		mm1,[eax+8]
		pfmul		mm0,mm0
		pfmul		mm1,mm1
		pfacc		mm0,mm0
		pfadd		mm0,mm1
		movd		len2,mm0
		femms
	}

	return len2;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline float Vector3::Length() const
{
//	return sqrtf( Length2() );

	float	len;

	__asm
	{
		femms
		mov 		eax,this
		movq		mm0,[eax]
		movd		mm1,[eax+8]
		pfmul		mm0,mm0
		pfmul		mm1,mm1
		pfacc		mm0,mm0
		pfadd		mm0,mm1
		pfrsqrt 	mm1,mm0
		movq		mm2,mm1
		pfmul		mm1,mm1
		pfrsqit1	mm1,mm0
		pfrcpit2	mm1,mm2
		pfmul		mm0,mm1
		movd		len,mm0
		femms
	}

	return len;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline float Vector3::ILength() const
{
//	float const len = Length();
//
//	assert( !Math::IsCloseToZero( len, Math::DEFAULT_FLOAT_TOLERANCE ) );
//
//	return ( !Math::IsCloseToZero( len ) ? 1.f / len : 1.f );

	float	ilen;

	__asm
	{
		femms
		mov 		eax,this
		movq		mm0,[eax]
		movd		mm1,[eax+8]
		pfmul		mm0,mm0
		pfmul		mm1,mm1
		pfacc		mm0,mm0
		pfadd		mm0,mm1
		pfrsqrt 	mm1,mm0
		movq		mm2,mm1
		pfmul		mm1,mm1
		pfrsqit1	mm1,mm0
		pfrcpit2	mm1,mm2
		movd		ilen,mm1
		femms
	}

	return ilen;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline float Vector3::ILength2() const
{
//	float const len2 = Length2();
//
//	assert( !Math::IsCloseToZero( len2, 2.0*Math::DEFAULT_FLOAT_TOLERANCE ) );
//
//	return ( !Math::IsCloseToZero( len2 ) ? 1.f / len2 : 1.f );

	float	ilen2;

	__asm
	{
		femms
		mov 		eax,this
		movq		mm0,[eax]
		movd		mm1,[eax+8]
		pfmul		mm0,mm0
		pfmul		mm1,mm1
		pfacc		mm0,mm0
		pfadd		mm0,mm1
		pfrcp		mm1,mm0
		pfrcpit1	mm0,mm1
		pfrcpit2	mm0,mm1
		movd		ilen2,mm0
		femms
	}

	return ilen2;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline bool Vector3::IsNormalized() const
{
	return ( Math::IsCloseTo( Length2(), 1.0, 2.0*Math::DEFAULT_FLOAT_NORMALIZED_TOLERANCE ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::Negate()
{
	m_X = -m_X;
	m_Y = -m_Y;
	m_Z = -m_Z;

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::Normalize()
{
//	return Scale( ILength() );

	__asm
	{
		femms
		mov 		eax,this
		movq		mm0,[eax]
		movd		mm1,[eax+8]
		movq		mm4,mm0
		movq		mm3,mm1
		pfmul		mm0,mm0 
		pfmul		mm1,mm1 
		pfacc		mm0,mm0 
		pfadd		mm0,mm1 
		pfrsqrt 	mm1,mm0 
		movq		mm2,mm1
		pfmul		mm1,mm1
		pfrsqit1	mm1,mm0
		pfrcpit2	mm1,mm2
		punpckldq	mm1,mm1
		pfmul		mm3,mm1
		pfmul		mm4,mm1
		movd		[eax+8],mm3
		movq		[eax],mm4
		femms
	}

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::Add( Vector3 const & b )
{
//	m_X += b.m_X;
//	m_Y += b.m_Y;
//	m_Z += b.m_Z;

	__asm
	{
		femms	
		mov 	eax,this
		mov 	edx,b
		movq	mm0,[eax]
		movd	mm1,[eax+8]
		pfadd	mm0,[edx]
		movd	mm2,[edx+8]
		pfadd	mm1,mm2
		movq	[eax],mm0
		movd	[eax+8],mm1
		femms	
	}

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::Subtract( Vector3 const & b )
{
//	m_X -= b.m_X;
//	m_Y -= b.m_Y;
//	m_Z -= b.m_Z;

	__asm
	{
		femms	
		mov 	eax,this
		mov 	edx,b
		movq	mm0,[eax]
		movd	mm1,[eax+8]
		pfsub	mm0,[edx]
		movd	mm2,[edx+8]
		pfsub	mm1,mm2
		movq	[eax],mm0
		movd	[eax+8],mm1
		femms	
	}

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::Scale( float scale )
{
//	m_X *= scale;
//	m_Y *= scale;
//	m_Z *= scale;

	__asm
	{
		femms
		mov 		eax,this
		movd		mm0,scale
		movq		mm3,[eax]
		punpckldq	mm0,mm0
		movd		mm2,[eax+8]
		movq		mm1,mm0
		pfmul		mm0,mm3
		pfmul		mm1,mm2 
		movq		[eax],mm0
		movd		[eax+8],mm1
		femms
	}

	return *this;
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::operator +=( Vector3 const & b )
{
	return Add( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::operator -=( Vector3 const & b )
{
	return Subtract( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::operator *=( float scale )
{
	return Scale( scale );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 const & Vector3::operator *=( Matrix33 const & m )
{
	return Transform( m );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//!
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

inline Vector3 const & Vector3::operator *=( Matrix43 const & m )
{
	return Transform( m );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 Vector3::operator -() const
{
	return Vector3( *this ).Negate();
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 Vector3::Origin()
{
	return Vector3( 0.0f, 0.0f, 0.0f );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 Vector3::XAxis()
{
	return Vector3( 1.0f, 0.0f, 0.0f );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 Vector3::YAxis()
{
	return Vector3( 0.0f, 1.0f, 0.0f );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 Vector3::ZAxis()
{
	return Vector3( 0.0f, 0.0f, 1.0f );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 operator +( Vector3 const & a, Vector3 const & b ) 
{
	return Vector3( a ).Add( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

inline Vector3 operator -( Vector3 const & a, Vector3 const & b )
{
	return Vector3( a ).Subtract( b );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3 operator *( Vector3 const & v, Matrix33 const & m )
{
	return Vector3( v ).Transform( m );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3 operator *( Matrix33 const &m , Vector3 const & v )
{
	return Vector3( v ).Transform( m );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

inline Vector3 operator *( Vector3 const & v, Matrix43 const & m )
{
	return Vector3( v ).Transform( m );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @note	When multiplying a vector and a matrix, the operator is commutative since the order of the operands is
//!			only notational.
//! @note	In order to multiply, a 4th element with the value of 1 is implicit.

inline Vector3 operator *( Matrix43 const & m, Vector3 const & v )
{
	return Vector3( v ).Transform( m );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3 operator *( Vector3 const & v, float s )
{
	return Vector3( v ).Scale( s );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! @note	When multiplying a vector and a scalar, the operator is commutative since the order of the operands is
//!			only notational.

inline Vector3 operator *( float s, Vector3 const & v )
{
	return Vector3( v ).Scale( s );
}
