
#include "utilities.h"

#include <algorithm>

std::ostream& operator<<(std::ostream& out, Magick::ColorRGB color) {
  out << "(" << color.red() << ", " << color.green() << ", " << color.blue()
      << ")";
  return out;
}

Magick::ColorRGB operator*(double t, Magick::ColorRGB color) {
  return Magick::ColorRGB(std::clamp((t * color.red()), 0.0, 1.0),
                          std::clamp((t * color.green()), 0.0, 1.0),
                          std::clamp((t * color.blue()), 0.0, 1.0));
}

Magick::ColorRGB operator*(Magick::ColorRGB color, double t) {
  return (t * color);
}

Magick::ColorRGB operator+(Magick::ColorRGB lhs, Magick::ColorRGB rhs) {
  return Magick::ColorRGB(std::clamp((lhs.red() + rhs.red()), 0.0, 1.0),
                          std::clamp((lhs.green() + rhs.green()), 0.0, 1.0),
                          std::clamp((lhs.blue() + rhs.blue()), 0.0, 1.0));
}

Magick::ColorRGB operator-(Magick::ColorRGB lhs, Magick::ColorRGB rhs) {
  return Magick::ColorRGB(std::clamp((lhs.red() - rhs.red()), 0.0, 1.0),
                          std::clamp((lhs.green() - rhs.green()), 0.0, 1.0),
                          std::clamp((lhs.blue() - rhs.blue()), 0.0, 1.0));
}
