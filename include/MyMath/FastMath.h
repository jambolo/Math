#pragma once

#if !defined(MYMATH_FASTMATH_H)
#define MYMATH_FASTMATH_H

namespace MyMath
{
//! @name AMD-Specific Implementations
//! @ingroup	Miscellaneous
//@{

#if 0
//! Returns 1.
inline float fld1()
{
    __asm fld1
    ;

//! Returns 0.
    inline float fldz()
    {
        __asm fldz
    }

//! Returns pi
    inline float fldpi()
    {
        __asm fldpi
    }

//! Returns ln 2
    inline float fldln2()
    {
        __asm fldln2
    }

//! Returns log2 e
    inline float fldl2e()
    {
        __asm fldl2e
    }

//! Returns log2 10
    inline float fldl2t()
    {
        __asm fldl2t
    }

//! Returns log10 2
    inline float fldlg2()
    {
        __asm fldlg2
    }

#endif // if 0

//! Returns the reciprocal square-root of @a x.
float frsqrt(float x) { return 1.0f / sqrtf(x); }

//! Returns the recipocal of @a x.
float frcp(float x) { return 1.0f / x; }

//! Returns sine and cosine of @a x.
void fsincos(float x, float * pSin, float * pCos) { *pSin = sinf(x); *pCos = cosf(x); }

//! Returns sine and 1 - cosine of @a x.
void fsinver(float x, float * pSin, float * pVers) { *pSin = sinf(x); *pVers = 1.0f - cosf(x); }

//@}
} // namespace MyMath

// Inline implementation

#if 0
namespace MyMath
{
//!
//! @param	x		operand

inline float frsqrt(float x)
{
    __asm
    {
        femms
        movd mm0, [x]
        pfrsqrt mm1, mm0; mm1 = 1 / sqrt(x), first pass
        movq mm2, mm1; save     initial 1 / sqrt(x) for Newton - Raphson
        pfmul mm1, mm1; compute a new 'x' by squaring sqrt(x)
        pfrsqit1 mm1, mm0; N - R 1 (uses original 'x' and approximated 'x')
        pfrcpit2 mm1, mm2; N - R 2 (uses 1 / sqrt(x) and result of N - R 1)
        movd        [x], mm1
        femms
    }

    return x;
}

//!
//! @param	x		operand

inline float frcp(float x)
{
    __asm
    {
        femms
        movd mm0, [x]
        pfrcp mm1, mm0; 1 / x, stage 1
        pfrcpit1 mm0, mm1; 1 / x, stage 2
        pfrcpit2 mm0, mm1; mm0 = 1 / x
                                 movd        [x], mm0
        femms
    }

    return x;
}

//! @param	x		operand
//! @param	pSin	Where to put sin(x)
//! @param	pCos	Where to put cos(x)

inline void fsincos(float x, float * pSin, float * pCos)
{
    __asm
    {
        fld dword ptr [x]
        mov eax, pCos
        fsincos
        mov edx, pSin
                  fstp        [eax]
        fstp        [edx]
    }
}

//! @param	x		operand
//! @param	pSin	Where to put sin(x)
//! @param	pVers	Where to put vers(x)

inline void fsinvers(float x, float * pSin, float * pVers)
{
    __asm
    {
        fld dword ptr [x]
        mov edx, pSin
        mov eax, pVers
        fsincos
        fld1
        fsub st, st(1)
        fstp        [eax]
        fstp        [edx]
    }
}
} // namespace MyMath

#endif // if 0

#endif // !defined(MYMATH_FASTMATH_H)
