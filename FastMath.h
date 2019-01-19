/** @file *//********************************************************************************************************

                                                      FastMath.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/Libraries/Math/FastMath.h#10 $

	$NoKeywords: $

 ********************************************************************************************************************/

#pragma once


namespace Math
{

//! @name AMD-Specific Implementations
//! @ingroup	Miscellaneous
//@{

//#pragma warning( push ) 
//#pragma warning( disable : 4035 )

//! Returns 1.
inline float fld1();

//! Returns 0.
inline float fldz();

//! Returns pi
inline float fldpi();

//! Returns ln 2
inline float fldln2();

//! Returns log2 e
inline float fldl2e();

//! Returns log2 10
inline float fldl2t();

//! Returns log10 2
inline float fldlg2();

//#pragma warning( pop )

//! Returns the reciprocal square-root of @a x.
float frsqrt( float x );

//! Returns the recipocal of @a x.
float frcp( float x );

//! Returns sine and cosine of @a x.
void fsincos( float x, float * pSin, float * pCos );

//! Returns sine and 1 - cosine of @a x.
void fsinver( float x, float * pSin, float * pVers );

//@}

} // namespace Math


// Inline implementation

#include "FastMath.inl"
