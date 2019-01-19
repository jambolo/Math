/** @file *//********************************************************************************************************

                                                     FixedPoint.h

						                    Copyright 2004, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/FixedPoint.h#2 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once



/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Fixed point representation
//
//! @param	T	Underlying integer type. The type must be signed.
//! @param	N	Number of bits in the fraction part

template< typename T, int N >
class FixedPoint
{
public:

	//! Default constructor (leaves the value uninitialized)
	FixedPoint();

	//! Constructor
	explicit FixedPoint( double x )
	{
		value = T( ldexp( x, N ) + 0.5 );
	}

	//! Constructor
	explicit FixedPoint( int x )
	{
		value = x << N;
	}

//	// Destructor
//	~FixedPoint();

	//! Conversion to double
	operator double() const
	{
		return ldexp( value, -N );
	}
	
	//! Conversion to int
	operator int() const
	{
		return (int)( ( value >> N ) & unsigned int(-1) );
	}

	//! Assignment from int
	FixedPoint & operator =( int rhs )
	{
		value = FixedPoint( rhs ).value;

		return *this;
	}

	//! Assignment from double
	FixedPoint & operator =( double rhs )
	{
		value = FixedPoint( rhs ).value;

		return *this;
	}

	//! += operator
	FixedPoint & operator +=( FixedPoint const & y )
	{
		value += y.value;

		return *this;
	}

	//! += operator
	FixedPoint & operator +=( int const & y )
	{
		value += FixedPoint( y ).value;

		return *this;
	}

	//! -= operator
	FixedPoint & operator -=( FixedPoint const & y )
	{
		value -= y.value;

		return *this;
	}

	//! -= operator
	FixedPoint & operator -=( int const & y )
	{
		value -= FixedPoint( y ).value;

		return *this;
	}

	//! *= operator
	FixedPoint & operator *=( FixedPoint const & y )
	{
		if ( sizeof( T ) == sizeof( int8 ) )
		{
			int16	temp;

			temp = int16( value ) * int16( y.value );
			value = (T)( temp / ( int16(1) << N ) & uint8(-1) );
		}
		else if ( sizeof( T ) == sizeof( int16 ) )
		{
			int32	temp;

			temp = int32( value ) * int32( y.value );
			value = (T)( temp / ( int32(1) << N ) & uint16(-1) );
		}
		else // if ( sizeof( T ) == sizeof( int32 ) )
		{
			int64	temp;

			temp = int64( value ) * int64( y.value );
			value = (T)( temp / ( int64(1) << N ) & uint32(-1) );
		}
//		else if ( sizeof( T ) == sizeof( int64 ) )
//		{
//			int128	temp;
//
//			temp = int128( value ) * int128( y.value );
//			value = (T)( temp / ( int128(1) << N ) & uint64(-1) );
//		}
//		else
//		{
//			T	temp[2];
//		}

		return *this;
	}

	//! *= operator
	FixedPoint & operator *=( int const & y )
	{
		value *= y;

		return *this;
	}

	//! /= operator
	FixedPoint & operator /=( FixedPoint const & y )
	{
		if ( sizeof( T ) == sizeof( int8 ) )
		{
			int16	temp;

			temp = int16( value ) * ( int16(1) << N ) / int16( y.value );
			value = (T)( temp & uint8(-1) );
		}
		else if ( sizeof( T ) == sizeof( int16 ) )
		{
			int32	temp;

			temp = int32( value ) * ( int32(1) << N ) / int32( y.value );
			value = (T)( temp & uint16(-1) );
		}
		else // if ( sizeof( T ) == sizeof( int32 ) )
		{
			int64	temp;

			temp = int64( value ) * ( int64(1) << N ) / int64( y.value );
			value = (T)( temp & uint32(-1) );
		}
//		else if ( sizeof( T ) == sizeof( int64 ) )
//		{
//			int128	temp;
//
//			temp = ( int128( value ) * ( int16(1) << N ) / int128( y.value );
//			value = (T)( temp ) & uint64(-1) );
//		}
//		else
//		{
//			T	temp[2];
//		}

		return *this;
	}

	//! /= operator
	FixedPoint & operator /=( int const & y )
	{
		value /= y;

		return *this;
	}

	//! negation operator
	FixedPoint & operator -()
	{
		value = -value;

		return *this;
	}

private:

	T	value;
};


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the sum of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x + y

template< typename T, int N >
FixedPoint<T, N> operator +( FixedPoint<T, N> const & x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) += y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the sum of a fixed-point and integer value.
//
//! @param	x	Fixed-point operand
//! @param	y	Integer operand
//! @return		x + y

template< typename T, int N >
FixedPoint<T, N> operator +( FixedPoint<T, N> const & x, int y )
{
	return ( FixedPoint<T, N>( x ) += FixedPoint<T, N>( y ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the sum of a fixed-point and integer value.
//
//! @param	x	Integer operand
//! @param	y	Fixed-point operand
//! @return		x + y

template< typename T, int N >
FixedPoint<T, N> operator +( int x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) += y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the difference of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x - y

template< typename T, int N >
FixedPoint<T, N> operator -( FixedPoint<T, N> const & x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) -= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the difference of a fixed-point and integer value.
//
//! @param	x	Fixed-point operand
//! @param	y	Integer operand
//! @return		x - y

template< typename T, int N >
FixedPoint<T, N> operator -( FixedPoint<T, N> const & x, int y )
{
	return ( FixedPoint<T, N>( x ) -= FixedPoint<T, N>( y ) );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the difference of a fixed-point and integer value.
//
//! @param	x	Integer operand
//! @param	y	Fixed-point operand
//! @return		x - y

template< typename T, int N >
FixedPoint<T, N> operator -( int x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) -= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the product of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x * y

template< typename T, int N >
FixedPoint<T, N> operator *( FixedPoint<T, N> const & x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) *= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the product of a fixed-point and integer value.
//
//! @param	x	Fixed-point operand
//! @param	y	Integer operand
//! @return		x * y

template< typename T, int N >
FixedPoint<T, N> operator *( FixedPoint<T, N> const & x, int y )
{
	return ( FixedPoint<T, N>( x ) *= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the product of a fixed-point and integer value.
//
//! @param	x	Integer operand
//! @param	y	Fixed-point operand
//! @return		x * y

template< typename T, int N >
FixedPoint<T, N> operator *( int x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( y ) *= x );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the division of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x / y

template< typename T, int N >
FixedPoint<T, N> operator /( FixedPoint<T, N> const & x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) /= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the division of a fixed-point and integer value.
//
//! @param	x	Fixed-point operand
//! @param	y	Integer operand
//! @return		x / y

template< typename T, int N >
FixedPoint<T, N> operator /( FixedPoint<T, N> const & x, int y )
{
	return ( FixedPoint<T, N>( x ) /= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the product of a fixed-point and integer value.
//
//! @param	x	Integer operand
//! @param	y	Fixed-point operand
//! @return		x * y

template< typename T, int N >
FixedPoint<T, N> operator /( int x, FixedPoint<T, N> const & y )
{
	return ( FixedPoint<T, N>( x ) /= y );
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the square root of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		sqrt( x )

template< typename T, int N >
FixedPoint<T, N> sqrt( FixedPoint<T, N> const & x )
{
	return FixedPoint<T, N>( sqrt( double( x ) ) );	//! @todo implement sqrt
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the sine of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		sin x

template< typename T, int N >
FixedPoint<T, N> sin( FixedPoint<T, N> const & x )
{
	return FixedPoint<T, N>( sin( double( x ) ) );	//! @todo implement sin
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the cosine of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		cos x

template< typename T, int N >
FixedPoint<T, N> cos( FixedPoint<T, N> const & x )
{
	return FixedPoint<T, N>( cos( double( x ) ) );	//! @todo implement cos
}


/********************************************************************************************************************/
/*																													*/
/********************************************************************************************************************/

//! Returns the tangent of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		tan( x )

template< typename T, int N >
FixedPoint<T, N> tan( FixedPoint<T, N> const & x )
{
	return FixedPoint<T, N>( tan( double( x ) ) );	//! @todo implement tan
}
