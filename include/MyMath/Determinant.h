/** @file *//********************************************************************************************************

                                                    Determinant.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Math/Determinant.h#9 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

//! @name Determinant Computation
//! @ingroup Matrices
//@{

//! Returns the determinant of a 2-by-2 matrix extracted from the specified matrix.
template <class M>
double Determinant2(M const & m, int r0 = 0, int r1 = 1, int c0 = 0, int c1 = 1)
{
    return double(m.m_M[r0][c0]) * double(m.m_M[r1][c1])
           - double(m.m_M[r0][c1]) * double(m.m_M[r1][c0]);
}

//! Returns the determinant of a 3-by-3 matrix extracted from the specified matrix.
template <class M>
double Determinant3(M const & m, int r0 = 0, int r1 = 1, int r2 = 2, int c0 = 0, int c1 = 1, int c2 = 2)
{
    return double(m.m_M[r0][c0]) * Determinant2<M>(m, r1, r2, c1, c2)
           - double(m.m_M[r0][c1]) * Determinant2<M>(m, r1, r2, c0, c2)
           + double(m.m_M[r0][c2]) * Determinant2<M>(m, r1, r2, c0, c1);
}

//! Returns the determinant of a 4-by-4 matrix extracted from the specified matrix.
template <class M>
double Determinant4(M const & m, int r0 = 0, int r1 = 1, int r2 = 2, int r3 = 3, int c0 = 0, int c1 = 1, int c2 = 2, int c3 = 3)
{
    return double(m.m_M[r0][c0]) * Determinant3<M>(m, r1, r2, r3, c1, c2, c3)
           - double(m.m_M[r0][c1]) * Determinant3<M>(m, r1, r2, r3, c0, c2, c3)
           + double(m.m_M[r0][c2]) * Determinant3<M>(m, r1, r2, r3, c0, c1, c3)
           - double(m.m_M[r0][c3]) * Determinant3<M>(m, r1, r2, r3, c0, c1, c2);
}

//@}
