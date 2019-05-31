#ifndef Vector2F_HPP
#define Vector2F_HPP

#include <cmath>
#include <ostream>
#include <array>

#include "Geometry.hpp"

class Vector2F;
typedef Vector2F VectorF;

class Vector2F
{
public:
	/// Good ol' rule of three
	/// CANIMPROVE: Implement rule of five, i.e. include move semantics when needed
	Vector2F (float x=0.0, float y=0.0) : m_components({{x, y}}) {} // double curly braces needed in C++11 for some reason
	Vector2F (Vector2F const& other) : m_components(other.m_components) {}
	Vector2F& operator= (Vector2F const& other);
	~Vector2F () {}

	// /// A point p can be considered as a vector from (0,0) to p
	// Vector2F (Point2F const& p) : m_components({{p.x, p.y}}) {}
	/// Construct a vector from one point to another point
	Vector2F (Point2F const& from, Point2F const& to)
		: m_components({{to.x-from.x, to.y-from.y}}) {}

	/// Standard arithmetic ops
	Point2F operator+ (Point2F const& p) const;
	Vector2F operator+ (Vector2F const& other) const;
	Vector2F const& operator+= (Vector2F const& other);
	Vector2F operator- (Vector2F const& other) const;
	Vector2F const& operator-= (Vector2F const& other);
	Vector2F operator* (float const scalar) const;
	Vector2F const& operator*= (float const scalar);
	Vector2F operator/ (float const scalar) const;
	Vector2F const& operator/= (float const scalar);
	// We define "Multiplication" with another vector as the dot product between the two
	float operator* (Vector2F const& other) const { return Dot(other); }

	bool operator== (Vector2F const& other) { return GetX() == other.GetX() && GetY() == other.GetY(); }

	/// Computes the inner angle (in radians) between the two vectors
	float Angle (Vector2F const& other) const;

	/// Dot product
	float Dot (Vector2F const& other) const;
	/// Cross product
	Vector2F Cross (Vector2F const& other) const;
	/// Norm/Magnitude/Length
	inline float Norm ()	const { return sqrt(Dot(*this)); }
	inline float Magnitude () const { return Norm(); } // A convenience	
	inline float Length () const { return Norm(); } // A convenience

	/// Normalize the vector (can be used as an lvalue)
	/// A normalized vector is resized such that its magnitude/norm is 1 while
	/// its direction stays the same. This is very useful when you want a vector
	/// for representing direction alone, such that the magnitude is irrelevant.
	Vector2F& Normalize ();
	Vector2F Normalize () const;

	/// Apply rotation on the vector
	Vector2F Rotate (float const theta) const;

	inline bool IsOrthogonalTo (Vector2F const& other) const { return Dot(other) == 0.0; }

	/// Convenient access to the vector's components
	inline void SetX (float const x) { m_components[0] = x; }
	inline void SetY (float const y) { m_components[1] = y; }
	inline float GetX ()	const { return m_components[0]; }
	inline float GetY ()	const { return m_components[1]; }

	friend std::ostream& operator<< (std::ostream& os, Vector2F const& v);

private:
	std::array<float, 2> m_components;
};

inline Vector2F& Vector2F::operator= (Vector2F const& other)
{
	m_components = other.m_components;
	return *this;
}

inline Point2F Vector2F::operator+ (Point2F const& p) const
{
	return Point2F(m_components[0] + p.x, m_components[1] + p.y);
}

inline Vector2F Vector2F::operator+ (Vector2F const& other) const
{
	return Vector2F(m_components[0] + other.m_components[0], m_components[1] + other.m_components[1]);
}

inline Vector2F const& Vector2F::operator+= (Vector2F const& other)
{
	return *this = *this + other;
}

inline Vector2F Vector2F::operator- (Vector2F const& other) const
{
	return Vector2F(m_components[0] - other.m_components[0], m_components[1] - other.m_components[1]);
}

inline Vector2F const& Vector2F::operator-= (Vector2F const& other)
{
	return *this = *this - other;
}

inline Vector2F Vector2F::operator* (float const scalar) const
{
	return Vector2F(m_components[0] * scalar, m_components[1] * scalar);
}

inline Vector2F const& Vector2F::operator*= (float const scalar)
{
	return *this = *this * scalar;
}

inline Vector2F Vector2F::operator/ (float const scalar) const
{
	return operator*(1.0/scalar);
}

inline Vector2F const& Vector2F::operator/= (float const scalar)
{
	return *this = *this / scalar;
}


inline float Vector2F::Angle (Vector2F const& other) const
{
	// P.Q = ||P|| * ||Q|| * cos(theta)
	// P.Q/(||P|| * ||Q||) = cos(theta)
	// Therefore, theta = arccos( P.Q/(||P|| * ||Q||) )
	return acos(Dot(other)/(Norm() * other.Norm()));
}

inline float Vector2F::Dot (Vector2F const& other) const
{
	return m_components[0]*other.m_components[0] + m_components[1]*other.m_components[1];
}

inline Vector2F& Vector2F::Normalize ()
{
	*this /= Norm();
	return *this;
}

inline Vector2F Vector2F::Normalize () const
{
	float norm = Norm();
	return operator/(norm);
}

inline std::ostream& operator<< (std::ostream& os, Vector2F const& v)
{
	os << "(" << v.m_components[0] << ", " << v.m_components[1] << " | " << v.Norm() << ")";

	return os;
}

#endif
