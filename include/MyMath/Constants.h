#pragma once

#if !defined(MYMATH_CONSTANTS_H)
#define MYMATH_CONSTANTS_H

namespace MyMath
{
//! @defgroup	Constants	Common Constants
//! @ingroup	Miscellaneous
//!
//! @note	These values have approximately 80 bits of accuracy.
//@{

double constexpr PI                 = 3.14159265358979323846264;
double constexpr TWO_PI             = 6.28318530717958647692529;
double constexpr PI_OVER_2          = 1.57079632679489661923132;
double constexpr PI_OVER_4          = 7.85398163397448309615661e-1;
double constexpr PI_OVER_8          = 3.92699081698724155807831e-1;
double constexpr PI_SQUARED         = 9.86960440108935861883449;
double constexpr ONE_OVER_PI        = 3.18309886183790671537768e-1;
double constexpr SQRT_OF_PI         = 1.77245385090551602729817;
double constexpr SQRT_OF_TWO_PI     = 2.50662827463100050241577;
double constexpr DEGREES_PER_RADIAN = 5.72957795130823208767982e1;
double constexpr RADIANS_PER_DEGREE = 1.74532925199432957692369e-2;

double constexpr E          = 2.71828182845904523536029;
double constexpr LOGE_OF_2  = 6.93147180559945309417232e-1;
double constexpr LOGE_OF_10 = 2.30258509299404568401799;
double constexpr LOG2_OF_E  = 1.44269504088896340735992;
double constexpr LOG2_OF_10 = 3.32192809488736234787032;
double constexpr LOG10_OF_E = 4.34294481903251827651129e-1;
double constexpr LOG10_OF_2 = 3.01029995663981195213739e-1;

double constexpr SQRT_OF_2        = 1.41421356237309504880169;
double constexpr SQRT_OF_2_OVER_2 = 7.07106781186547524400844e-1;
double constexpr SQRT_OF_3        = 1.73205080756887729352745;
double constexpr SQRT_OF_3_OVER_3 = 5.77350269189625764509149e-1;

//@}
} // namespace MyMath

#endif // !defined(MYMATH_CONSTANTS_H)
