
/// \file

#ifndef _VEC3_H_
#define _VEC3_H_

#include <cmath>
#include <iostream>

/// A 3 dimensional vector class to represent vectors and points.
class Vec3 {
 private:
  double x_{0.0}, y_{0.0}, z_{0.0};
  static const int kSize_ = 3;

 public:
  /// The default constructor for Vec3 creates a Vec3 initialized
  /// to a zero vector.
  Vec3() = default;

  /// Constructor to initialize a Vec3 with \p x, \p y, and \p z.
  Vec3(double x, double y, double z) : x_{x}, y_{y}, z_{z} {};

  /// Return the value of x
  /// \returns the value of x_
  [[nodiscard]] double x() const;

  /// Return the value of y
  /// \returns the value of y_
  [[nodiscard]] double y() const;

  /// Return the value of z
  /// \returns the value of z_
  [[nodiscard]] double z() const;

  /// Return the number of components in the vector; always 3.
  /// \returns the size of the vector, always 3.
  [[nodiscard]] int size() const;

  /// Negation operator
  /// \returns a copy of *this negated.
  Vec3 operator-() const;

  /// Operator [], the subscript operator, which allows the object to be treated
  /// like a a C array. This is a const version so it can only be used for
  /// reading. Vec3 foo{1, 2, 3}; double val = foo[1];
  /// \param i is the subscript 0, 1, or 2
  /// \returns x_ for 0, y_ for 1, z_ for 2
  /// \throws std::out_of_range if \p i is not 0, 1, or 2
  double operator[](int i) const noexcept(false);

  /// Operator [], the subscript operator,  which allows the object to be
  /// treated like a a C array. This is a non-const version which returns a
  /// reference so it can be used for writing. Vec3 foo{1, 2, 3}; foo[1] = 42;
  /// \param i is the subscript 0, 1, or 2
  /// \returns x_ for 0, y_ for 1, z_ for 2
  /// \throws std::out_of_range if \p i is not 0, 1, or 2
  double& operator[](int i) noexcept(false);

  /// Calculate the length of a vector using the distance formula.
  /// d = sqrt(x*x + y*y + z*z)
  /// \returns the length of the vector
  [[nodiscard]] double length() const;

  /// Calculate the squared length of a vector using the distance formula.
  /// This is fast and useful when one wants to compare relative distances
  /// or when you wish to determine if a vector is of unit length.
  /// d = x*x + y*y + z*z
  /// \returns the squared length of the vector
  [[nodiscard]] double length_squared() const;
};

/// Sum \p lhs and \p rhs together
/// \param lhs The left hand operand of the operator
/// \param rhs The right hand operand of the operator
/// \returns The sum of \p lhs and \p rhs as a new Vec3.
Vec3 operator+(const Vec3& lhs, const Vec3& rhs);

/// Difference of \p lhs and \p rhs together
/// \param lhs The left hand operand of the operator
/// \param rhs The right hand operand of the operator
/// \returns The difference of \p lhs and \p rhs as a new Vec3.
Vec3 operator-(const Vec3& lhs, const Vec3& rhs);

/// Product of \p lhs and \p rhs
/// Where \p lhs is a scalar value and \p rhs is a Vec3, scale \p rhs with \p
/// lhs. \param lhs The left hand operand of the operator \param rhs The right
/// hand operand of the operator \returns The product of \p lhs and \p rhs as a
/// new Vec3.
Vec3 operator*(double lhs, const Vec3& rhs);

/// Product of \p lhs and \p rhs
/// Where \p rhs is a scalar value and \p lhs is a Vec3, scale \p lhs with \p
/// rhs. \param lhs The left hand operand of the operator \param rhs The right
/// hand operand of the operator \returns The product of \p rhs and \p lhs as a
/// new Vec3.
Vec3 operator*(const Vec3& lhs, double rhs);

/// Quotient of \p lhs and \p rhs
/// Where \p rhs is a scalar value and \p lhs is a Vec3, scale \p lhs with
/// 1/rhs.
/// \param lhs The left hand operand of the operator
/// \param rhs The right hand operand of the operator
/// \returns The product of \p rhs and \p lhs as a new Vec3.
/// \throws std::domain_error if \p rhs is 0
Vec3 operator/(const Vec3& lhs, double rhs) noexcept(false);

/// Compare \p lhs and \p rhs to see if they have the same values
/// Where \p lhs is a Vec3 and \p rhs is a Vec3, compare the two component by
/// component to see if they are equivalent.
/// \param lhs The left hand operand of the operator
/// \param rhs The right hand operand of the operator
/// \returns True if lhs and rhs have the same values, False otherwise.
bool operator==(const Vec3& lhs, const Vec3& rhs);

/// Compare \p lhs and \p rhs to see if they have different values
/// Where \p lhs is a Vec3 and \p rhs is a Vec3, compare the two component by
/// component to see if they are different.
/// \param lhs The left hand operand of the operator
/// \param rhs The right hand operand of the operator
/// \returns True if lhs and rhs have at least one value that is different,
/// False otherwise.
bool operator!=(const Vec3& lhs, const Vec3& rhs);

/// The dot product of two Vec3 objects.
/// The [dot product](https://en.wikipedia.org/wiki/Dot_product) is
/// the cosine of the angle formed between the two Vec3 objects scaled by
/// the magnitude of the Vec3.
/// \param u The left hand operand of the operator
/// \param v The right hand operand of the operator
/// \returns The dot product between u and v.
double Dot(const Vec3& u, const Vec3& v);

/// The cross product of two Vec3 objects.
/// The cross product of two vectors yields a third which is mutally
/// orthogonal to the first two.
// \param u The first vector.
// \param v The second vector.
Vec3 Cross(const Vec3& u, const Vec3& v);

/// Return a unit length (length == 1.0) vector given the vector \p v.
/// \param v The vector to be resized to unit length
/// \returns A vector of unit length
/// \throws std::domain_error if the length of \p v is zero
/// \remark This function does not handle degenerate cases where the vector's
/// length is 0.
Vec3 UnitVector(const Vec3& v) noexcept(false);

/// Return the reflected vector given the normal \p n and the incoming
/// direction vector \p v.
/// \param v The incoming vector direction
/// \param n The normal to the surface
/// \returns the reflection vector
Vec3 Reflect(const Vec3& v, const Vec3& n);

/// Convert a Vec3 object into a string so it can be printed.
/// This is a function which defines a new behavior for the << operator.
/// A Vec3 inialized like so Vec3(1.1, 2.2, 3.3)
/// will output as "(1.1, 2.2, 3.3)"
/// \param out An output stream such as cout
/// \param v A Vec3 object
/// \returns The ostream that was passed
std::ostream& operator<<(std::ostream& out, const Vec3& v);

// A fancy C++ trick!
// Namespace aliases, see
// https://en.cppreference.com/w/cpp/language/namespace_alias

/// A 3D point and a 3D vector are very similar. For the sake of this
/// application we shall make a namespace alias so that Point3 means the
/// same thing as Vec3. (Be warned that mathematically a 3D point is not
/// the same thing as a 3D vector.)
using Point3 = Vec3;

#endif