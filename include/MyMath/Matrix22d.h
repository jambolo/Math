#pragma once

#if !defined(MYMATH_MATRIX22D_H)
#define MYMATH_MATRIX22D_H

class Vector2d;
class Matrix22;

#pragma warning( push )
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

//! A 2x2 matrix of doubles.
//
//! @ingroup Matrices
//!

class Matrix22d
{
public:

    //! Constructor
    Matrix22d() = default;

    //! Constructor
    Matrix22d(double Xx, double Xy,
              double Yx, double Yy);

    //! Constructor
    Matrix22d(Vector2d const & x,  Vector2d const & y);

    //! Constructor
    explicit Matrix22d(double const * pM);

    //! Conversion
    explicit Matrix22d(Matrix22 const & m22);

    //! Returns the X vector.
    Vector2d const & GetX() const;

    //! Returns the Y vector.
    Vector2d const & GetY() const;

    //! Returns the determinant.
    double Determinant() const;

    //! Returns true if the matrix is orthonormal (within a tolerance)
    bool IsOrthonormal() const;

    //! Transposes the matrix. Returns the result.
    Matrix22d & Transpose();

    //! Inverts the matrix. Returns the result.
    Matrix22d & Invert();

    //! Pre-multiplies a matrix. Returns the result.
    Matrix22d & PreConcatenate(Matrix22d const & b);

    //! Post-multiplies a matrix. Returns the result.
    Matrix22d & PostConcatenate(Matrix22d const & b);

    //! Post-multiplies a matrix. Returns the result.
    Matrix22d & operator *=(Matrix22d const & b);

    //! Returns the inverse.
    Matrix22d operator ~() const;

    union
    {
        double m_M[2][2];               //!< Elements as a 2x2 array
        struct
        {
            //! @name	Matrix elements
            //@{
            double /** */ m_Xx, /** */ m_Xy;
            double /** */ m_Yx, /** */ m_Yy;
            //@}
        };
    };

    //! Returns the identity matrix
    static Matrix22d Identity();
};

#pragma warning( pop )

// Inline functions

inline Matrix22d::Matrix22d(double Xx, double Xy,
                            double Yx, double Yy)

    : m_Xx(Xx)
    , m_Xy(Xy)
    , m_Yx(Yx)
    , m_Yy(Yy)
{
}

inline Vector2d const & Matrix22d::GetX() const
{
    return *reinterpret_cast<Vector2d const *>(&m_Xx);
}

inline Vector2d const & Matrix22d::GetY() const
{
    return *reinterpret_cast<Vector2d const *>(&m_Yx);
}

inline Matrix22d & Matrix22d::operator *=(Matrix22d const & b)
{
    return PostConcatenate(b);
}

inline Matrix22d Matrix22d::operator ~() const
{
    return Matrix22d(*this).Invert();
}

inline Matrix22d Matrix22d::Identity()
{
    return Matrix22d(1.0, 0.0,
                     0.0, 1.0);
}

#endif // !defined(MYMATH_MATRIX22D_H)
