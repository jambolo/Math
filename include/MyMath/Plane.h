#pragma once

#if !defined(MYMATH_PLANE_H)
#define MYMATH_PLANE_H

#include "Intersectable.h"
#include "Vector3.h"

class Matrix43;
class Poly;
class HalfSpace;

//! A plane that can detect and compute intersections with other intersectable objects.
//!
//! @ingroup Geometry
//!

class Plane : public Intersectable
{
public:

    //! Constructor.
    Plane() = default;

    //! Constructor.
    explicit Plane(Vector3 const & distance); // Vector from 0 to plane

    //! Constructor.
    Plane(Vector3 const & normal, float d); // Normal and distance from 0

    //! Constructor.
    Plane(Vector3 const & normal, Point const & point); // Normal and point in the plane

    //! Constructor.
    Plane(float a, float b, float c, float d); // aX + bY +cZ + d = 0

    //! Destructor.
    virtual ~Plane() override = default;

    //! @name Overrides Intersectable
    //@{
    virtual Result IntersectedBy(Intersectable const * pI) const override { return pI->Intersects(*this);                       }
    virtual Result Intersects(Point const & point) const override         { return Intersectable::Intersects(*this, point);     }
    virtual Result Intersects(Line const & line) const override           { return Intersectable::Intersects(*this, line);      }
    virtual Result Intersects(Ray const & ray) const override             { return Intersectable::Intersects(*this, ray);       }
    virtual Result Intersects(Segment const & segment) const override     { return Intersectable::Intersects(*this, segment);   }
    virtual Result Intersects(Plane const & plane) const override         { return Intersectable::Intersects(*this, plane);     }
    virtual Result Intersects(HalfSpace const & halfspace) const override { return Intersectable::Intersects(*this, halfspace); }
    virtual Result Intersects(Poly const & poly) const override           { return Intersectable::Intersects(*this, poly);      }
    virtual Result Intersects(Sphere const & sphere) const override       { return Intersectable::Intersects(*this, sphere);    }
    virtual Result Intersects(Cone const & cone) const override           { return Intersectable::Intersects(*this, cone);      }
    virtual Result Intersects(AABox const & aabox) const override         { return Intersectable::Intersects(*this, aabox);     }
    virtual Result Intersects(Box const & box) const override             { return Intersectable::Intersects(*this, box);       }
    virtual Result Intersects(Frustum const & frustum) const override     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    //! Returns the distance to the point in the direction of the normal.
    float DirectedDistance(Point const & point) const;

    //! Returns a point reflected about the plane.
    Point Reflect(Point const & point) const;

    //! Returns a Vector reflected about the plane.
    Vector3 ReflectVector(Vector3 const & v) const;

    //! Returns the location of a point projected along the plane's normal onto the plane.
    Point Project(Point const & point) const;

    //! Returns the location of a point projected along a vector onto the plane.
    Point Project(Point const & point, Vector3 const & v) const;

    //! Returns the result of projecting a vector onto the plane.
    Vector3 ProjectVector(Vector3 const & v) const;

    //! Returns a 4x3 matrix that reflects a point around the plane.
    Matrix43 GetReflectionMatrix() const;

    //! Returns a 4x3 matrix that projects a point along the normal onto the plane.
    Matrix43 GetProjectionMatrix() const;

    //! Returns a 4x3 matrix that projects a point along a vector onto the plane.
    Matrix43 GetProjectionMatrix(Vector3 const & v) const;

    //! Returns true if the point is in front of the plane.
    bool IsInFrontOf(Point const & v) const;

    //! Returns true if the point is behind the plane.
    bool IsBehind(Point const & v) const;

    // Plane equation: m_N.m_X * x + m_N.m_Y * y + m_N.m_Z * z + m_D = 0

    Vector3 m_N;            //!< Normal ([A, B, C])
    float m_D;              //!< Distance (D)
};

//! A planar polygon that can detect and compute intersections with other intersectable objects
//!
//! @ingroup Geometry
//!

class Poly : public Plane
{
public:

    //! Constructor.
    Poly() = default;

    //! Constructor.
    Poly(Vector3 const * paVertices, int nVertices);

    //! Constructor.
    Poly(Plane const & plane, Vector3 const * paVertices, int nVertices);

    //! Destructor.
    virtual ~Poly() override = default;

    //! @name Overrides Intersectable
    //@{
    virtual Result IntersectedBy(Intersectable const * pI) const override { return pI->Intersects(*this);                       }
    virtual Result Intersects(Point const & point) const override         { return Intersectable::Intersects(*this, point);     }
    virtual Result Intersects(Line const & line) const override           { return Intersectable::Intersects(*this, line);      }
    virtual Result Intersects(Ray const & ray) const override             { return Intersectable::Intersects(*this, ray);       }
    virtual Result Intersects(Segment const & segment) const override     { return Intersectable::Intersects(*this, segment);   }
    virtual Result Intersects(Plane const & plane) const override         { return Intersectable::Intersects(*this, plane);     }
    virtual Result Intersects(HalfSpace const & halfspace) const override { return Intersectable::Intersects(*this, halfspace); }
    virtual Result Intersects(Poly const & poly) const override           { return Intersectable::Intersects(*this, poly);      }
    virtual Result Intersects(Sphere const & sphere) const override       { return Intersectable::Intersects(*this, sphere);    }
    virtual Result Intersects(Cone const & cone) const override           { return Intersectable::Intersects(*this, cone);      }
    virtual Result Intersects(AABox const & aabox) const override         { return Intersectable::Intersects(*this, aabox);     }
    virtual Result Intersects(Box const & box) const override             { return Intersectable::Intersects(*this, box);       }
    virtual Result Intersects(Frustum const & frustum) const override     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    //! @name Overrides Plane
    //@{
    //	float DirectedDistance( Vector3 const & point ) const;
    //	Vector3 Reflect( Vector3 const & point ) const;
    //	Vector3 ReflectVector( Vector3 const & v ) const;
    //	Vector3 Project( Vector3 const & point ) const;
    //	Vector3 Project( Vector3 const & point, Vector3 const & v ) const;
    //	Vector3 ProjectVector( Vector3 const & v ) const;
    //	Matrix43 GetReflectionMatrix() const;
    //	Matrix43 GetProjectionMatrix() const;
    //	Matrix43 GetProjectionMatrix( Vector3 const & v ) const;
    //	bool IsInFrontOf( Vector3 const & v ) const;
    //	bool IsBehind( Vector3 const & v ) const;
    //@}

    Vector3 * m_paVertices;         //!< Vertex list
    int m_nVertices;                //!< Number of vertices in the vertex list
};

//! A half-space that can detect and compute intersections with other intersectable objects
//!
//! @ingroup Geometry
//!

class HalfSpace : public Intersectable
{
public:

    //! Constructor.
    HalfSpace() = default;

    //! Constructor.
    HalfSpace(Plane const & plane);

    //! Destructor.
    virtual ~HalfSpace() override = default;

    //! @name Overrides Intersectable
    //@{
    virtual Result IntersectedBy(Intersectable const * pI) const override { return pI->Intersects(*this);                       }
    virtual Result Intersects(Point const & point) const override         { return Intersectable::Intersects(*this, point);     }
    virtual Result Intersects(Line const & line) const override           { return Intersectable::Intersects(*this, line);      }
    virtual Result Intersects(Ray const & ray) const override             { return Intersectable::Intersects(*this, ray);       }
    virtual Result Intersects(Segment const & segment) const override     { return Intersectable::Intersects(*this, segment);   }
    virtual Result Intersects(Plane const & plane) const override         { return Intersectable::Intersects(*this, plane);     }
    virtual Result Intersects(HalfSpace const & halfspace) const override { return Intersectable::Intersects(*this, halfspace); }
    virtual Result Intersects(Poly const & poly) const override           { return Intersectable::Intersects(*this, poly);      }
    virtual Result Intersects(Sphere const & sphere) const override       { return Intersectable::Intersects(*this, sphere);    }
    virtual Result Intersects(Cone const & cone) const override           { return Intersectable::Intersects(*this, cone);      }
    virtual Result Intersects(AABox const & aabox) const override         { return Intersectable::Intersects(*this, aabox);     }
    virtual Result Intersects(Box const & box) const override             { return Intersectable::Intersects(*this, box);       }
    virtual Result Intersects(Frustum const & frustum) const override     { return Intersectable::Intersects(*this, frustum);   }
    //@}

    Plane m_Plane; //!< The plane that defines the half-space.
};

#include "Point.h"
#include "Vector3.h"

//! This function constructs a plane whose distance from the origin is the length of @a distance, and whose normal
//! points in the direction of @a distance.
//!
//! @param	distance	A vector describing the orientation of the plane and its distance from the origin

inline Plane::Plane(Vector3 const & distance)
{
    float const length = distance.Length();

    if (!MyMath::IsCloseToZero(length))
    {
        m_D  = -length;
        m_N  = distance;
        m_N *= 1.f / length;
    }
    else
    {
        m_D = 0.;
        m_N = Vector3::XAxis();
    }
}

//! This function constructs a plane with the given normal and distance from the origin.
//!
//! @param	normal	The plane's normal. This vector must be normalized.
//! @param	d		Distance from the origin (in the direction of the normal)

inline Plane::Plane(Vector3 const & normal, float d)
    : m_N(normal)
    , m_D(-d)
{
    assert(normal.IsNormalized());
}

//! This function constructs a plane given the normal and the position of a point in the plane.
//!
//! @param	normal		The plane's normal. This vector must be normalized.
//! @param	point		The position of a point in the plane

inline Plane::Plane(Vector3 const & normal, Point const & point)
    : m_N(normal)
    , m_D(Dot(normal, point.value_))
{
    assert(normal.IsNormalized());
}

//! This function constructs a plane that is described by the formula <em>a</em>x + <em>b</em>y + <em>c</em>z +
//! <em>d</em> = 0. The function normalizes the parameters before storing them.
//!
//! @param	a,b,c,d		Plane parameters

inline Plane::Plane(float a, float b, float c, float d)
    : m_N(a, b, c)
    , m_D(d)
{
    assert(!MyMath::IsCloseToZero(m_N.Length()));

    float const ilength = m_N.ILength();

    m_D *= ilength;
    m_N *= ilength;
}

//!
//! @param	point	Point to reflect

inline Point Plane::Reflect(Point const & point) const
{
    return point.value_ - m_N * (DirectedDistance(point) * 2.f);
}

//!
//! @param	v	Vector to reflect

inline Vector3 Plane::ReflectVector(Vector3 const & v) const
{
    return v - m_N * (Dot(m_N, v) * 2.f);
}

//!
//! @param	point	Point to project

inline Point Plane::Project(Point const & point) const
{
    return Point(point.value_ - m_N * DirectedDistance(point));
}

//! @param	point	Point to project
//! @param	v		Vector to project along

inline Point Plane::Project(Point const & point, Vector3 const & v) const
{
    float const nDotV = Dot(m_N, v);

    return (MyMath::IsCloseToZero(nDotV)) ?
           point.value_ - v * DirectedDistance(point) :
           point.value_ - v * (DirectedDistance(point) / nDotV);
}

//!
//! @param	v		Vector to project

inline Vector3 Plane::ProjectVector(Vector3 const & v) const
{
    return v - m_N * Dot(m_N, v);
}

inline bool Plane::IsInFrontOf(Point const & v) const
{
    return DirectedDistance(v) > 0.f;
}

inline bool Plane::IsBehind(Point const & v) const
{
    return DirectedDistance(v) < 0.f;
}

inline float Plane::DirectedDistance(Point const & point) const
{
    return Dot(m_N, point.value_) + m_D;
}

inline HalfSpace::HalfSpace(Plane const & plane)
    : m_Plane(plane)
{
}

#endif // !defined(MYMATH_PLANE_H)
