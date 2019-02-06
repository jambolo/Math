#pragma once

#if !defined(MYMATH_RANGE_H)
#define MYMATH_RANGE_H

#include "Misc/Assertx.h"

namespace MyMath
{
//! @defgroup	Range			Range
//! @ingroup	Miscellaneous
//@{

//! A range between two values.
//!
//! @param	T				Value type. @a T can be any type that implements operator== and operator<
//! @param	lower_closed	If true, the lower end of the range is included in the range
//! @param	upper_closed	If true, the upper end of the range is included in the range

template <typename T, bool lower_closed = true, bool upper_closed = true>
class Range
{
public:

    //! Constructor.
    //! @param	lower	Lower end of the range
    //! @param	upper	Upper end of the range
    //! @note	@a upper cannot be less then @a lower
    Range(T lower, T upper) : m_Lower(lower)
        , m_Upper(upper) { assert(!(upper < lower)); }

    //! Returns the upper end of the range.
    T const & Upper() const { return m_Upper; }

    //! Returns the lower end of the range.
    T const & Lower() const { return m_Lower; }

private:

    T const m_Lower;    //!< The lower end of the range.
    T const m_Upper;    //!< The upper end of the range.
};

//! @name Comparison Operators
//@{

//! Returns true if the range is less than b.
template <typename T, bool lower_closed, bool upper_closed>
bool operator <(Range<T, lower_closed, upper_closed> const & a, T const & b)
{
    //	a < b if
    //		l,u] :	u < b
    //		l,u) :	u <= b, or b >= u, or !( b < u )

    return (upper_closed &&  (a.Upper() < b)) ||
           (!upper_closed && !(b < a.Upper()));
}

//! Returns true if the range is greater than b.
template <typename T, bool lower_closed, bool upper_closed>
bool operator >(Range<T, lower_closed, upper_closed> const & a, T const & b)
{
    //	a > b if
    //		[l,u :	l > b, or b < l
    //		(l,u :	l >= b, or !( l < b )

    return (lower_closed &&  (b < a.Lower())) ||
           (!lower_closed && !(a.Lower() < b));
}

//! Returns true if the range is less than or includes b.
template <typename T, bool lower_closed, bool upper_closed>
bool operator <=(Range<T, lower_closed, upper_closed> const & a, T const & b)
{
    //	a <= b if
    //		[l,u :	l <= b, or b >= l, or !( b < l )
    //		(l,u :	l < b

    return (lower_closed && !(b < a.Lower())) ||
           (!lower_closed &&  (a.Lower() < b));
}

//! Returns true if the range is greater than or includes b.
template <typename T, bool lower_closed, bool upper_closed>
bool operator >=(Range<T, lower_closed, upper_closed> const & a, T const & b)
{
    //	a >= b if
    //		l,u] :	u >= b, or !( u < b )
    //		l,u) :	u > b, or !( b < u )

    return (upper_closed && a.Upper() >= b) ||
           (!upper_closed && a.Upper() >  b);
}

//! Returns true if the range includes b.
template <typename T, bool lower_closed, bool upper_closed>
bool operator ==(Range<T, lower_closed, upper_closed> const & a, T const & b)
{
    return a <= b && a >= b;
}

//! Returns true if the range does not include b.
template <typename T, bool lower_closed, bool upper_closed>
bool operator !=(Range<T, lower_closed, upper_closed> const & a, T const & b)
{
    return a < b || a > b;
}

//! Returns true if a is less than the range.
template <typename T, bool lower_closed, bool upper_closed>
bool operator <(T const & a, Range<T, lower_closed, upper_closed> const & b)
{
    return b > a;
}

//! Returns true if a is greater than the range.
template <typename T, bool lower_closed, bool upper_closed>
bool operator >(T const & a, Range<T, lower_closed, upper_closed> const & b)
{
    return b < a;
}

//! Returns true if a is within or less than the range.
template <typename T, bool lower_closed, bool upper_closed>
bool operator <=(T const & a, Range<T, lower_closed, upper_closed> const & b)
{
    return b >= a;
}

//! Returns true if a is within or greater than the range.
template <typename T, bool lower_closed, bool upper_closed>
bool operator >=(T const & a, Range<T, lower_closed, upper_closed> const & b)
{
    return b <= a;
}

//! Returns true if a is within the range.
template <typename T, bool lower_closed, bool upper_closed>
bool operator ==(T const & a, Range<T, lower_closed, upper_closed> const & b)
{
    return b == a;
}

//! Returns true if a is not within the range.
template <typename T, bool lower_closed, bool upper_closed>
bool operator !=(T const & a, Range<T, lower_closed, upper_closed> const & b)
{
    return b != a;
}

//@}
} // namespace MyMath

#endif // !defined(MYMATH_RANGE_H)
