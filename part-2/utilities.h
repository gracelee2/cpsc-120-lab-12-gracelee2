
/// \file

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <Magick++.h>

#include <iostream>

/// Output insertion operator for Magick::ColorRGB. Makes it easy to print
/// a Magick::ColorRGB to an ostream like cout.
/// \param out An ostream such as cout
/// \param Magick::ColorRGB An RGB color
/// \returns The ostream that was passed
std::ostream& operator<<(std::ostream& out, Magick::ColorRGB color);

/// Multiply an RGB color by a double, clamp the values to be between 0 and 1
/// inclusively.
/// \param t A positive scalar value
/// \param color An RGB color
/// \returns A new Magick::ColorRGB, the values are clamped between 0 and 1
Magick::ColorRGB operator*(double t, Magick::ColorRGB color);

/// Multiply an RGB color by a double, clamp the values to be between 0 and 1
/// inclusively.
/// \param t A positive scalar value
/// \param color An RGB color
/// \returns A new Magick::ColorRGB, the values are clamped between 0 and 1
Magick::ColorRGB operator*(Magick::ColorRGB colorm, double t);

/// Add two RGB colors together and return the sum as a new color. Each channel
/// is summed with the same channel of the other color variable.
/// \param lhs The left hand side color value
/// \param rhs The right hand side color value
/// \returns A new color that is the sum of lhs and rhs by channel
Magick::ColorRGB operator+(Magick::ColorRGB lhs, Magick::ColorRGB rhs);

/// Subtract two RGB colors from each other and return the sum as a
/// new color. Each channel is summed with the same channel of the other
/// color variable.
/// \param lhs The left hand side color value
/// \param rhs The right hand side color value
/// \returns A new color that is the sum of lhs and rhs by channel
Magick::ColorRGB operator-(Magick::ColorRGB lhs, Magick::ColorRGB rhs);

#endif