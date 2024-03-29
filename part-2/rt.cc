// Grace Lee
// CPSC 120-01
// 2021-10-28
// grace1@csu.fullerton.edu
// @gracelee2
//
// Lab 08-01
//
// This program determines the color of the ray
//
/// \file

#include <Magick++.h>

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "ray.h"
#include "rng.h"
#include "utilities.h"
#include "vec3.h"

using namespace std;
using namespace Magick;

/// RayColor computes the color the ray \p r sees through the camera lens.
/// Given a Ray \p r, calculate the color that is visible to the ray.
/// In this iteration, the ray can only see the sky. The color of the sky
/// smoothly changes between the \c sky_top color and the \c sky_bttom color.
/// As the names suggest, \c sky_top is the color of the sky at the top of
/// the image and \c sky_bottom is the color of the sky at the bottom of
/// the image.
///
/// \param r A ray eminating from the camera through the scene
/// \returns The color visible from that ray

ColorRGB RayColor(const Ray& r) {
  ColorRGB c;
  // Greenish brown
  ColorRGB sky_top(.5, .4, 0);
  // Bluish purple
  ColorRGB sky_bottom(.2, .1, .5);
  Vec3 unit_direction = UnitVector(r.direction());
  double t = 0.5 * (unit_direction.y() + 1.0);
  c = (1.0 - t) * sky_bottom + t * sky_top;
  // TODO: Calculate the color c that is visible to Ray r.
  return c;
}

/// Main function - Entry point for our ray tracer
/// The program takes one argument which is the output file name. Specify a
/// filename with an ending the GraphicsMagick knows how to write out as an
/// image file such as png, jpg, jpeg, gif, etc.
int main(int argc, char const* argv[]) {
  InitializeMagick(*argv);
  auto args = vector<string>(argv, argv + argc);
  if (args.size() < 3) {
    cout << "Please provide a path to a file.\n";
    exit(1);

  }
  // TODO: Process the command line arguemnts. Save args.at(1) to
  // output_file_name.
  string output_file_name;
  output_file_name = args.at(1);


  /// Image definition in main
  /// The image is the output from the virtual camera. The image is what
  /// you will see when you open the output in an image viewer. The image's
  /// dimensions are specified in pixels and are therefore in integer units.
  /// The aspect ratio represents the ratio of width / height. The ratio
  /// 16:9 is the ratio used for wide format movies. Traditional 35mm film
  /// photographs have an image that is 36 mm x 24 mm which has an aspect
  /// ratio of 36:24 or 1.5.
  const double kAspectRatio = 16.0 / 9.0;
  // Set the image width to 400 pixels
  const int kImageWidth = 512;
  // Calculate the height of the image using the width and aspect ratio.
  // Remember to round the number to the closest integer.
  const int kImageHeight = int(lround(kImageWidth / kAspectRatio));
  // Create a new Image object using the file name provided on the
  // command line.
  ColorRGB yellow(1, 1, 0);
  // Create a yellow image the size that we'd like. Use yellow or some
  // obviously wrong color (a color not in our image)to help us debug
  // our output.
  Image image(Geometry(kImageWidth, kImageHeight), yellow);
  // Print out some information about the image to help us debug what's
  // going on.
  cout << "Your image has " << image.columns() << " columns (x direction) and "
       << image.rows() << " rows (y direction).\n";

  /// Camera definition in main
  /// The [viewport](https://en.wikipedia.org/wiki/Viewport) is the
  /// rectangular viewing region visible to the camera. You can think of it
  /// as the dimensions of the camera's film or sensor. The coordinates
  /// are specfied in floating point units (doubles). Unlike an image which
  /// has its dimensions expressed as pixels, the camera's viewport dimensions
  /// can be expressed in whatever units you would like to use. Since we are
  /// creating a make believe image of make believe things, you can imagine
  /// the size of the objects to be as small (millimeters) or as large
  /// (kilometers) as you like.
  // The height of the viewport
  const double kViewportHeight = 2.0;
  // The width of the viewport is calculated using the height and the
  // previously defined aspect ratio.
  const double kViewportWidth = kAspectRatio * kViewportHeight;
  // The focal length is the distance between the projection plane (the end
  // of the lens) and the projection point (the inside of the camera).
  const double kFocalLength = 1.0;
  // The origin is as we expect. Everything in our world will be measured
  // from the center of the camera.
  const Point3 kOrigin{0, 0, 0};
  // Create a vector that represents the horizontal direction with respect
  // to the viewport.
  const Vec3 kHorizontal{kViewportWidth, 0, 0};
  // Create a vecotr that represents the vertical direction with respect
  // to the viewport
  const Vec3 kVertical{0, kViewportHeight, 0};
  // Calculate a vector that starts at the origin and points to the lower
  // left hand corner of the viewport. We will use this when we generate
  // all the rays that emanate out from the viewplane.
  const Vec3 kLowerLeftCorner =
      kOrigin - kHorizontal / 2 - kVertical / 2 - Vec3(0, 0, kFocalLength);

  /// Rendering the image in main
  /// Using nested loops, start from the top row of the viewplane and
  /// calculate the color for each pixel in each column of the image.
  /// The image (the output file) is the result of this calculation so
  /// keep in mind that each ray that is created maps onto a pixel in the
  /// image.
  // Save the starting time so the elapsed time can
  // be calculated.
  chrono::time_point<chrono::high_resolution_clock> start =
      chrono::high_resolution_clock::now();

  // TODO: Write a triply nested for loop.
  //  - The outer most loop is the loop that controls how many images are
  //    created.
  //  - The middle loop is for each column in the image
  //  - The inner most loop is for each row in the image

  for (int column = int(image.columns() - 1); column >= 0; column--) {
    for (int row = 0; row < image.rows(); row++) {
      assert(row < image.rows());
      assert(column < image.columns());
      double u = NAN;
      u = column/ image.columns()-1;
      double v = NAN;
      v = row/ image.rows()-1;
      Vec3 point_in_image_plane = kLowerLeftCorner + u * kHorizontal + v * kVertical;
      Ray r(kOrigin, point_in_image_plane - kOrigin);
      ColorRGB pixel_color;
      pixel_color = RayColor(r);
      image.pixelColor(column, row, pixel_color);
}
}

  // Use this at the top of your inner most for loop to help catch errors.
  // This is a way to make sure you don't accidentally have the wrong
  // logic in your for loops. What an assertion does is it says this must
  // be true and if it isn't then the program is going to halt with an
  // error message. If your program halts, then you know you have
  // something wrong with your for loop counters.


  // u is the distance from the left edge of the image to the right
  // edge of the image measured as a percentage.
  // The column divided by the image.width() - 1 is the percentage of
  // the distance from the left side of the image to the right.
  // Consider column = 0 then colum / (image.columns() - 1) -> 0.0
  //          if column == (image.columns() - 1) / 2 then
  //             column / (image.columns() - 1) -> 0.5
  //          if column == (image.columns() - 1) then
  //             column / (image.columns() - 1) -> 1.0
  // The same is true for v
  // TODO: Assign u as the ratio of the current column to the total number of
  // columns.

  // TODO: Assign v as the ratio of the current row to the total number of rows.

  // TODO: Declare and construct Ray r that starts at the camera's center,
  // the origin (kOrigin), and travels through the pixel center defined by
  // kLowerLeftCorner + u * kHorizontal + v * kVertical - kOrigin

  // TODO: Calculate and return the color at the pixel that Ray r
  // points through and assign it to pixel_color. Use the
  // fucntion RayColor()

  // It may help you to debug what you are doing by printing
  // each pixel out. Remember you can always resize the image to be
  // something smaller by changing kImageWidth and recompiling.
  // Remember column is the x direction and row is the y direction.
  // cout << column << ":" << row << " " << pixel_color << "\n";

  // TODO: Set the color for pixel(row, column) to the calculated color,
  //image.pixelColor(column, row, r);

  // Our work is done, save the ending time
  chrono::time_point<chrono::high_resolution_clock> end =
      chrono::high_resolution_clock::now();

  // TODO: Write the images to an output file, for example
// image.write(output_file_name);
image.write(output_file_name);
  // Calculate the elapsed time by taking the difference between end
  // and start.
  chrono::duration<double> elapsed_seconds = end - start;

  // Display the elapsed number of seconds.
  cout << "Time elapsed: " << elapsed_seconds.count() << " seconds.\n";

  return 0;
}
