// Grace Lee
// CPSC 120-01
// 2021-10-28
// grace1@csu.fullerton.edu
// @gracelee2
//
// Lab 08-01
//
// This program determines the color of the ray

#include "vec3.h"

// See the header file for documentation.

[[nodiscard]] double Vec3::x() const {
  return x_;
  // TODO: Implement this member function given the documentation in vec3.h
}

[[nodiscard]] double Vec3::y() const {
  return y_;
  // TODO: Implement this member function given the documentation in vec3.h
}

[[nodiscard]] double Vec3::z() const {
  return z_;
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 Vec3::operator-() const {
  const Vec3& lhs = *this;
  return Vec3(-lhs[0], -lhs[1], -lhs[2]);
  // TODO: Implement this member function given the documentation in vec3.h
}

double Vec3::operator[](int i) const noexcept(false) {
  double rv = NAN;
  if (i == 0) {
    return x_;
  } else if (i == 1) {
    return y_;
  } else if (i == 2) {
    return z_;
  } else {
    throw std::out_of_range("Index out of range. Must be between 0 and 2.");
  }
  // TODO: Implement this member function given the documentation in vec3.h
  return rv;
}

double& Vec3::operator[](int i) noexcept(false) {
  // Yes, this will generate a linter warning:
  // readability-else-after-return
  // Since we are ignoring switch statements in CPSC 120, there does not
  // exist a CPSC 120 friendly way to write the logic below other than
  // using returns after elses.
  if (i == 0) {
    return x_;
  } else if (i == 1) {
    return y_;
  } else if (i == 2) {
    return z_;
  } else {
    throw std::out_of_range("Index out of range. Must be between 0 and 2.");
  }
}

// Yes, this will generate a linter warning:
// readability-convert-member-functions-to-static
// For the sake of CPSC 120, we will leave this as a member function
// although it is better off being a static class function.
[[nodiscard]] int Vec3::size() const {
  return 3;
  // TODO: Implement this member function given the documentation in vec3.h
}

[[nodiscard]] double Vec3::length() const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
  // TODO: Implement this member function given the documentation in vec3.h
}

[[nodiscard]] double Vec3::length_squared() const {
  return (x_ * x_) + (y_ * y_) + (z_ * z_);
  // TODO: Implement this member function given the documentation in vec3.h
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  out << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
  // TODO: Implement this member function given the documentation in vec3.h
  return out;
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
  return Vec3{lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z()};
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
  return Vec3{lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z()};
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 operator*(double lhs, const Vec3& rhs) {
  return Vec3{lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z()};
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 operator*(const Vec3& lhs, double rhs) {
  return Vec3{rhs * lhs.x(), rhs * lhs.y(), rhs * lhs.z()};
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 operator/(const Vec3& lhs, double rhs) noexcept(false) {
  if (rhs == 0.0) {
    throw std::domain_error("t is zero; divide by zero exception.");
  }
  return (1.0 / rhs) * lhs;
}

bool operator==(const Vec3& lhs, const Vec3& rhs) {
  bool status = true;
  double epsilon = 1e-7;
  for (int i = 0; i < lhs.size(); i++) {
    double a = lhs[i];
    double b = rhs[i];
    status = status && ((a == b) || ((a - epsilon) < b && (a + epsilon) > b));
  }
  return status;
}

bool operator!=(const Vec3& lhs, const Vec3& rhs) { return not(lhs == rhs); }

double Dot(const Vec3& u, const Vec3& v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 Cross(const Vec3& u, const Vec3& v) {
  return Vec3{u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x()};
  // TODO: Implement this member function given the documentation in vec3.h
}

Vec3 UnitVector(const Vec3& v) noexcept(false) {
  double length = v.length();
  if (length == 0.0) {
    throw std::domain_error("v.length() is zero; divide by zero exception.");
  }
  return v / v.length();
}

Vec3 Reflect(const Vec3& v, const Vec3& n) { return (2 * Dot(v, n) * n) - v; }
