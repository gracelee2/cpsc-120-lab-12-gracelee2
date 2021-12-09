// Grace Lee
// CPSC 120-01
// 2021-10-28
// grace1@csu.fullerton.edu
// @gracelee2
//
// Lab 08-01
//
// This program determines the color of the ray

#include "ray.h"

[[nodiscard]] Point3 Ray::origin() const {
  return kOrigin;
  // TODO: Implement this member function given the documentation in ray.h
}

[[nodiscard]] Vec3 Ray::direction() const {
  return direction;
  // TODO: Implement this member function given the documentation in ray.h
}

[[nodiscard]] Point3 Ray::at(double t) const {
  
  // TODO: Implement this member function given the documentation in ray.h
}

std::ostream& operator<<(std::ostream& out, const Ray& r) {
  // TODO: Implement this member function given the documentation in ray.h
  return out;
}
