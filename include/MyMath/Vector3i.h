#pragma once

#if !defined(MYMATH_VECTOR3I_H)
#define MYMATH_VECTOR3I_H

#include <iosfwd>

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 3D vector of integers.
//!
//! @ingroup Vectors
//!

class Vector3i
{
public:

    //! Constructor.
    Vector3i() = default;

    //! Constructor.
    Vector3i(int x, int y, int z);

    //! Constructor.
    Vector3i(int const v[3]);

    //! Negates the vector. Returns the result.
    Vector3i const & Negate();

    //! Adds a vector. Returns the result.
    Vector3i const & Add(Vector3i const & b);

    //! Subtracts a vector. Returns the result.
    Vector3i const & Subtract(Vector3i const & b);

    //! Multiplies the vector by a scalar. Returns the result.
    Vector3i const & Scale(int scale);

    //! Adds a vector. Returns the result.
    Vector3i const & operator +=(Vector3i const & b);

    //! Subtracts a vector. Returns the result.
    Vector3i const & operator -=(Vector3i const & b);

    //! Scales the vector. Returns the result.
    Vector3i const & operator *=(int scale);

    //! Returns the negative.
    Vector3i operator -() const;

    //! Returns the sum.
    Vector3i operator +(Vector3i const & b) const;

    //! Returns the difference.
    Vector3i operator -(Vector3i const & b) const;

    union
    {
        int m_V[3];     //!< Elements as an array {x, y, z}
        struct
        {
            int /** */ m_X, m_Y, m_Z;
        };
    };

    // Useful constants

    //! Returns [0, 0, 0].
    static Vector3i Origin();

    //! Returns [1, 0, 0].
    static Vector3i XAxis();

    //! Returns [0, 1, 0].
    static Vector3i YAxis();

    //! Returns [0, 0, 1].
    static Vector3i ZAxis();
};

#pragma warning( pop )

//! @name Vector3i Binary Operators
//! @ingroup Vectors
//@{

//! Returns the result of scaling v by s.
Vector3i operator *(Vector3i const & v, int s);

//! Returns the result of scaling v by s.
Vector3i operator *(int s, Vector3i const & v);

//@}

//! @name Vector3i Insert/Extract Operators
//! @ingroup Vectors
//@{

//! Extracts a Vector3i from a stream
std::istream & operator >>(std::istream & in, Vector3i & v);

//! Inserts a Vector3i into a stream
std::ostream & operator <<(std::ostream & out, Vector3i const & v);

//@}

// Inline functions

inline Vector3i::Vector3i(int x, int y, int z)
    : m_X(x)
    , m_Y(y)
    , m_Z(z)
{
}

inline Vector3i::Vector3i(int const v[3])
    : m_X(v[0])
    , m_Y(v[1])
    , m_Z(v[2])
{
}

// inline int Vector3i::Length2() const
// {
////	return ( m_X * m_X + m_Y * m_Y + m_Z * m_Z );
//
//	int	len;
//
//	__asm
//	{
//		femms
//		mov         eax,this
//		movq		mm0,[eax]
//		movd		mm1,[eax+8]
//		pfmul		mm0,mm0
//		pfmul		mm1,mm1
//		pfacc		mm0,mm0
//		pfadd		mm0,mm1
//		movd		len,mm0
//		femms
//	}
//
//	return len;
// }
//
// inline int Vector3i::Length() const
// {
////	return sqrtf( Length2() );
//
//	int	len;
//
//	__asm
//	{
//		femms
//		mov         eax,this
//		movq		mm0,[eax]
//		movd		mm1,[eax+8]
//		pfmul		mm0,mm0
//		pfmul		mm1,mm1
//		pfacc		mm0,mm0
//		pfadd		mm0,mm1
//		pfrsqrt     mm1,mm0
//		movq		mm2,mm1
//		pfmul		mm1,mm1
//		pfrsqit1	mm1,mm0
//		pfrcpit2	mm1,mm2
//		pfmul		mm0,mm1
//		movd		len,mm0
//		femms
//	}
//
//	return len;
// }
//
// inline int Vector3i::ILength() const
// {
////	int const len = Length();
////
////	assert( !MyMath::IsCloseToZero( len ) );
////
////	return ( !MyMath::IsCloseToZero( len ) ? 1 / len : 1 );
//
//	int	len;
//
//	__asm
//	{
//		femms
//		mov         eax,this
//		movq		mm0,[eax]
//		movd		mm1,[eax+8]
//		pfmul		mm0,mm0
//		pfmul		mm1,mm1
//		pfacc		mm0,mm0
//		pfadd		mm0,mm1
//		pfrsqrt     mm1,mm0
//		movq		mm2,mm1
//		pfmul		mm1,mm1
//		pfrsqit1	mm1,mm0
//		pfrcpit2	mm1,mm2
//		movd		len,mm1
//		femms
//	}
//
//	return len;
// }
//
// inline bool Vector3i::IsNormalized() const
// {
//	return ( MyMath::IsCloseTo( Length2(), 1., 2.*MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE ) );
// }
//
// inline Vector3i const & Vector3i::Negate()
// {
//	m_X = -m_X;
//	m_Y = -m_Y;
//	m_Z = -m_Z;
//
//	return *this;
// }
//
// inline Vector3i const & Vector3i::Normalize()
// {
////	return Scale( ILength() );
//
//	__asm
//	{
//		femms
//		mov         eax,this
//		movq		mm0,[eax]
//		movd		mm1,[eax+8]
//		movq		mm4,mm0
//		movq		mm3,mm1
//		pfmul		mm0,mm0
//		pfmul		mm1,mm1
//		pfacc		mm0,mm0
//		pfadd		mm0,mm1
//		pfrsqrt     mm1,mm0
//		movq		mm2,mm1
//		pfmul		mm1,mm1
//		pfrsqit1	mm1,mm0
//		pfrcpit2	mm1,mm2
//		punpckldq	mm1,mm1
//		pfmul		mm3,mm1
//		pfmul		mm4,mm1
//		movd		[eax+8],mm3
//		movq		[eax],mm4
//		femms
//	}
//
//	return *this;
// }
//
// inline Vector3i const & Vector3i::Add( Vector3i const & b )
// {
////	m_X += b.m_X;
////	m_Y += b.m_Y;
////	m_Z += b.m_Z;
//
//	__asm
//	{
//		femms
//		mov     eax,this
//		mov     edx,b
//		movq	mm0,[eax]
//		movd	mm1,[eax+8]
//		pfadd	mm0,[edx]
//		movd	mm2,[edx+8]
//		pfadd	mm1,mm2
//		movq	[eax],mm0
//		movd	[eax+8],mm1
//		femms
//	}
//
//	return *this;
// }
//
// inline Vector3i const & Vector3i::Subtract( Vector3i const & b )
// {
////	m_X -= b.m_X;
////	m_Y -= b.m_Y;
////	m_Z -= b.m_Z;
//
//	__asm
//	{
//		femms
//		mov     eax,this
//		mov     edx,b
//		movq	mm0,[eax]
//		movd	mm1,[eax+8]
//		pfsub	mm0,[edx]
//		movd	mm2,[edx+8]
//		pfsub	mm1,mm2
//		movq	[eax],mm0
//		movd	[eax+8],mm1
//		femms
//	}
//
//	return *this;
// }
//
// inline Vector3i const & Vector3i::Scale( int scale )
// {
////	m_X *= scale;
////	m_Y *= scale;
////	m_Z *= scale;
//
//	__asm
//	{
//		femms
//		mov         eax,this
//		movd		mm0,scale
//		movq		mm3,[eax]
//		punpckldq	mm0,mm0
//		movd		mm2,[eax+8]
//		movq		mm1,mm0
//		pfmul		mm0,mm3
//		pfmul		mm1,mm2
//		movq		[eax],mm0
//		movd		[eax+8],mm1
//		femms
//	}
//
//	return *this;
// }
//
// inline Vector3i const & Vector3i::operator +=( Vector3i const & b )
// {
//	return Add( b );
// }
//
// inline Vector3i const & Vector3i::operator -=( Vector3i const & b )
// {
//	return Subtract( b );
// }
//
// inline Vector3i const & Vector3i::operator *=( int scale )
// {
//	return Scale( scale );
// }
//
// inline Vector3i const & Vector3i::operator *=( Matrix33 const & m )
// {
//	return Transform( m );
// }
//
/////
///// @note	In order to multiply, a 4th element with the value of 1 is implicit.
//
// inline Vector3i const & Vector3i::operator *=( Matrix43 const & m )
// {
//	return Transform( m );
// }
//
// inline Vector3i Vector3i::operator -() const
// {
//	return Vector3i( *this ).Negate();
// }
//
// inline Vector3i Vector3i::operator +( Vector3i const & b ) const
// {
//	return Vector3i( *this ).Add( b );
// }
//
// inline Vector3i Vector3i::operator -( Vector3i const & b ) const
// {
//	return Vector3i( *this ).Subtract( b );
// }
//
// inline Vector3i Vector3i::operator *( Matrix33 const & m ) const
// {
//	return Vector3i( *this ).Transform( m );
// }
//
/////
///// @note	In order to multiply, a 4th element with the value of 1 is implicit.
//
// inline Vector3i Vector3i::operator *( Matrix43 const & m ) const
// {
//	return Vector3i( *this ).Transform( m );
// }

inline Vector3i Vector3i::Origin()
{
    return Vector3i(0, 0, 0);
}

inline Vector3i Vector3i::XAxis()
{
    return Vector3i(1, 0, 0);
}

inline Vector3i Vector3i::YAxis()
{
    return Vector3i(0, 1, 0);
}

inline Vector3i Vector3i::ZAxis()
{
    return Vector3i(0, 0, 1);
}

// inline Vector3i operator *( Vector3i const & v, int s )
// {
//	return Vector3i( v ).Scale( s );
// }
//
// inline Vector3i operator *( int s, Vector3i const & v )
// {
//	return Vector3i( v ).Scale( s );
// }

#endif // !defined(MYMATH_VECTOR3I_H)
