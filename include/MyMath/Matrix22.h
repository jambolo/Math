#pragma once

#if !defined(MYMATH_MATRIX22_H)
#define MYMATH_MATRIX22_H

class Vector2;
class Matrix22d;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 2x2 matrix of floats.
//!
//! @ingroup Matrices
//!

class Matrix22
{
public:

    //! Constructor.
    Matrix22() = default;

    //! Constructor.
    Matrix22(float xx, float xy,
             float yx, float yy);

    //! Constructor.
    Matrix22(Vector2 const & x,  Vector2 const & y);

    //! Constructor.
    explicit Matrix22(float const * pM);

    //! Conversion
    explicit Matrix22(Matrix22d const & m22d);

    //! Returns the X vector.
    Vector2 const & GetX() const;

    //! Returns the Y vector.
    Vector2 const & GetY() const;

    //! Returns the determinant.
    double Determinant() const;

    //! Returns true if the matrix is orthonormal (within a tolerance)
    bool IsOrthonormal() const;

    //! Transposes the matrix. Returns the result.
    Matrix22 & Transpose();

    //! Inverts the matrix. Returns the result.
    Matrix22 & Invert();

    //! Pre-multiplies a matrix. Returns the result.
    Matrix22 & PreConcatenate(Matrix22 const & b);

    //! Post-multiplies a matrix. Returns the result.
    Matrix22 & PostConcatenate(Matrix22 const & b);

    //! Post-multiplies a matrix. Returns the result.
    Matrix22 & operator *=(Matrix22 const & b);

    //! Returns the inverse.
    Matrix22 operator ~() const;

    union
    {
        float m_M[2][2];            //!< Elements as a 2x2 array.
        struct
        {
            //! @name Matrix elements
            //@{
            float /** */ m_Xx, /** */ m_Xy;
            float /** */ m_Yx, /** */ m_Yy;
            //@}
        };
    };

    //! Returns the identity matrix
    static Matrix22 Identity();
};

#pragma warning( pop )

// Inline functions

inline Matrix22::Matrix22(float Xx, float Xy,
                          float Yx, float Yy)

    : m_Xx(Xx)
    , m_Xy(Xy)
    , m_Yx(Yx)
    , m_Yy(Yy)
{
}

inline Vector2 const & Matrix22::GetX() const
{
    return *reinterpret_cast<Vector2 const *>(&m_Xx);
}

inline Vector2 const & Matrix22::GetY() const
{
    return *reinterpret_cast<Vector2 const *>(&m_Yx);
}

inline Matrix22 & Matrix22::operator *=(Matrix22 const & b)
{
    return PostConcatenate(b);
}

inline Matrix22 Matrix22::operator ~() const
{
    return Matrix22(*this).Invert();
}

inline Matrix22 Matrix22::Identity()
{
    return Matrix22(1.0f, 0.0f,
                    0.0f, 1.0f);
}

#endif // !defined(MYMATH_MATRIX22_H)
