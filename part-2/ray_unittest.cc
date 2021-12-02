
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include "ray.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <sstream>
#include <string>

namespace {

class RayTest : public testing::Test {
 protected:
  void SetUp() override {
    r1_ = Ray(Point3(1.1, 2.2, 3.3), Vec3(3.5, 8.2, 5.1));
    r2_ = Ray(Point3(3.1, 4.2, 5.3), Vec3(0.323, 0.985, 0.455));
  }

  // void TearDown() override { }

  Ray r1_;
  Ray r2_;
};

TEST_F(RayTest, GetOrigin) {
  EXPECT_TRUE(Point3(1.1, 2.2, 3.3) == r1_.origin());
  EXPECT_TRUE(Point3(3.1, 4.2, 5.3) == r2_.origin());
}

TEST_F(RayTest, GetDirection) {
  EXPECT_TRUE(Vec3(3.5, 8.2, 5.1) == r1_.direction());
  EXPECT_TRUE(Vec3(0.323, 0.985, 0.455) == r2_.direction());
}

TEST_F(RayTest, At) {
  EXPECT_TRUE(Point3(1.1, 2.2, 3.3) == r1_.at(0));
  EXPECT_TRUE(Point3(3.1, 4.2, 5.3) == r2_.at(0));
  EXPECT_TRUE(Point3(1.1, 2.2, 3.3) + Vec3(3.5, 8.2, 5.1) == r1_.at(1));
  EXPECT_TRUE(Point3(3.1, 4.2, 5.3) + Vec3(0.323, 0.985, 0.455) == r2_.at(1));
  EXPECT_TRUE((Point3(3.1, 4.2, 5.3) + (Vec3(0.323, 0.985, 0.455) * 0.5)) ==
              r2_.at(0.5));
}

TEST_F(RayTest, StreamInsertionOperator) {
  std::ostringstream message_buffer;
  message_buffer << r1_;
  EXPECT_TRUE(message_buffer.str() ==
              "Ray(origin=(1.1, 2.2, 3.3), direction=(3.5, 8.2, 5.1))");
  message_buffer = std::ostringstream();
  message_buffer << r2_;
  EXPECT_TRUE(message_buffer.str() ==
              "Ray(origin=(3.1, 4.2, 5.3), direction=(0.323, 0.985, 0.455))");
}

}  // namespace
