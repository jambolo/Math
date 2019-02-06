#pragma once

#if !defined(MYMATH_FIXEDPOINT_H)
#define MYMATH_FIXEDPOINT_H

//! Fixed point representation
//!
//! @param	T	Underlying integer type. The type must be signed.
//! @param	N	Number of bits in the fraction part

template <typename T, int N>
class FixedPoint
{
public:

    //! Default constructor (leaves the value uninitialized)
    FixedPoint() = default;

    //! Constructor.
    FixedPoint(double x)
    {
        value = T(ldexp(x, N) + 0.5);
    }

    //! Constructor.
    FixedPoint(int x)
    {
        value = x << N;
    }

    template <typename U, int M>
    FixedPoint(FixedPoint<U, M> x)
    {
        if (M < N)
            value = T(x.value) << (N - M);
        else
            value = T(x.value / (1 << (M - N)));
    }

    //! Destructor.
    ~FixedPoint() = default;

    //! Conversion to double
    operator double() const
    {
        return ldexp(value, -N);
    }

    //! Conversion to long
    operator long() const
    {
        return (long)((value >> N) & unsigned long(-1));
    }

    //! += operator
    FixedPoint & operator +=(FixedPoint const & y)
    {
        value += y.value;
        return *this;
    }

    //! -= operator
    FixedPoint & operator -=(FixedPoint const & y)
    {
        value -= y.value;
        return *this;
    }

    //! *= operator
    FixedPoint & operator *=(FixedPoint const & y)
    {
        if (sizeof(T) == sizeof(int8_t))
        {
            int16_t temp;

            temp  = int16_t(value) * int16_t(y.value);
            value = (T)(temp / (int16_t(1) << N) & uint8(-1));
        }
        else if (sizeof(T) == sizeof(int16_t))
        {
            int32_t temp;

            temp  = int32_t(value) * int32_t(y.value);
            value = (T)(temp / (int32_t(1) << N) & uint16(-1));
        }
        else         // if ( sizeof( T ) == sizeof( int32_t ) )
        {
            int64_t temp;

            temp  = int64_t(value) * int64_t(y.value);
            value = (T)(temp / (int64_t(1) << N) & uint32(-1));
        }
//      else // if ( sizeof( T ) == sizeof( int64_t ) )
//      {
//          int128_t	temp;
//
//          temp = int128_t( value ) * int128_t( y.value );
//          value = (T)( temp / ( int128_t(1) << N ) & uint64(-1) );
//      }
//		else
//		{
//			T	temp[2];
//		}
        return *this;
    }

    //! /= operator
    FixedPoint & operator /=(FixedPoint const & y)
    {
        if (sizeof(T) == sizeof(int8_t))
        {
            int16_t temp;

            temp  = int16_t(value) * (int16_t(1) << N) / int16_t(y.value);
            value = (T)(temp & uint8(-1));
        }
        else if (sizeof(T) == sizeof(int16_t))
        {
            int32_t temp;

            temp  = int32_t(value) * (int32_t(1) << N) / int32_t(y.value);
            value = (T)(temp & uint16(-1));
        }
        else         // if ( sizeof( T ) == sizeof( int32_t ) )
        {
            int64_t temp;

            temp  = int64_t(value) * (int64_t(1) << N) / int64_t(y.value);
            value = (T)(temp & uint32(-1));
        }
//		else if ( sizeof( T ) == sizeof( int64_t ) )
//		{
//			int128_t	temp;
//
//			temp = ( int128_t( value ) * ( int16_t(1) << N ) / int128_t( y.value );
//			value = (T)( temp ) & uint64(-1) );
//		}
//		else
//		{
//			T	temp[2];
//		}
        return *this;
    }

    //! negation operator
    FixedPoint & operator -()
    {
        value = -value;
        return *this;
    }

private:

    T value;
};

//! Returns the sum of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x + y

template <typename T, int N>
FixedPoint<T, N> operator +(FixedPoint<T, N> x, FixedPoint<T, N> const & y)
{
    return x += y;
}

//! Returns the difference of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x - y

template <typename T, int N>
FixedPoint<T, N> operator -(FixedPoint<T, N> x, FixedPoint<T, N> const & y)
{
    return x -= y;
}

//! Returns the product of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x * y

template <typename T, int N>
FixedPoint<T, N> operator *(FixedPoint<T, N> x, FixedPoint<T, N> const & y)
{
    return x *= y;
}

//! Returns the division of two fixed-point values.
//
//! @param	x	Fixed-point operand
//! @param	y	Fixed-point operand
//! @return		x / y

template <typename T, int N>
FixedPoint<T, N> operator /(FixedPoint<T, N> x, FixedPoint<T, N> const & y)
{
    return x /= y;
}

//! Returns the square root of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		sqrt( x )

template <typename T, int N>
FixedPoint<T, N> sqrt(FixedPoint<T, N> const & x)
{
    return FixedPoint<T, N>(sqrt(double(x)));             //! @todo implement sqrt
}

//! Returns the sine of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		sin x

template <typename T, int N>
FixedPoint<T, N> sin(FixedPoint<T, N> const & x)
{
    return FixedPoint<T, N>(sin(double(x)));             //! @todo implement sin
}

//! Returns the cosine of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		cos x

template <typename T, int N>
FixedPoint<T, N> cos(FixedPoint<T, N> const & x)
{
    return FixedPoint<T, N>(cos(double(x)));             //! @todo implement cos
}

//! Returns the tangent of a fixed-point value.
//
//! @param	x	Fixed-point operand
//! @return		tan( x )

template <typename T, int N>
FixedPoint<T, N> tan(FixedPoint<T, N> const & x)
{
    return FixedPoint<T, N>(tan(double(x)));             //! @todo implement tan
}

#endif // !defined(MYMATH_FIXEDPOINT_H)
