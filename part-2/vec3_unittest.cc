
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include "vec3.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <sstream>
#include <string>

namespace {

class Vec3Test : public testing::Test {
 protected:
  void SetUp() override {
    v1_ = Vec3(1.1, 2.2, 3.3);
    v2_ = Vec3(3.1, 4.2, 5.3);
  }

  // void TearDown() override { }

  Vec3 zero_;
  Vec3 v1_;
  Vec3 v2_;
};

TEST_F(Vec3Test, GetX) {
  EXPECT_DOUBLE_EQ(0, zero_.x());
  EXPECT_DOUBLE_EQ(1.1, v1_.x());
  EXPECT_DOUBLE_EQ(3.1, v2_.x());
}

TEST_F(Vec3Test, GetY) {
  EXPECT_DOUBLE_EQ(0, zero_.y());
  EXPECT_DOUBLE_EQ(2.2, v1_.y());
  EXPECT_DOUBLE_EQ(4.2, v2_.y());
}

TEST_F(Vec3Test, GetZ) {
  EXPECT_DOUBLE_EQ(0, zero_.z());
  EXPECT_DOUBLE_EQ(3.3, v1_.z());
  EXPECT_DOUBLE_EQ(5.3, v2_.z());
}

TEST_F(Vec3Test, UnaryMinus) {
  EXPECT_TRUE(zero_ == -zero_);
  EXPECT_TRUE(Vec3(-1.1, -2.2, -3.3) == -v1_);
  EXPECT_TRUE(Vec3(-3.1, -4.2, -5.3) == -v2_);
  EXPECT_TRUE(v2_ != -v2_);
}

TEST_F(Vec3Test, Size) {
  EXPECT_DOUBLE_EQ(3, zero_.size());
  EXPECT_DOUBLE_EQ(3, v1_.size());
  EXPECT_DOUBLE_EQ(3, v2_.size());
}

TEST_F(Vec3Test, SubscriptOperator) {
  EXPECT_DOUBLE_EQ(0, zero_[0]);
  EXPECT_DOUBLE_EQ(2.2, v1_[1]);
  EXPECT_DOUBLE_EQ(5.3, v2_[2]);
  double x = v1_[1];
  EXPECT_DOUBLE_EQ(2.2, x);

  EXPECT_THROW(
      {
        try {
          v1_[7];
        } catch (std::out_of_range const& e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("Index out of range. Must be between 0 and 2.",
                       e.what());
          throw;
        }
      },
      std::out_of_range);

  EXPECT_THROW(
      {
        try {
          x = v1_[7];
        } catch (std::out_of_range const& e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("Index out of range. Must be between 0 and 2.",
                       e.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST_F(Vec3Test, Length) {
  EXPECT_DOUBLE_EQ(0, zero_.length());
  EXPECT_DOUBLE_EQ(4.1158231254513353, v1_.length());
  EXPECT_DOUBLE_EQ(7.4390859653589168, v2_.length());
}

TEST_F(Vec3Test, LengthSquared) {
  EXPECT_DOUBLE_EQ(0, zero_.length_squared());
  EXPECT_DOUBLE_EQ(16.939999999999998, v1_.length_squared());
  EXPECT_DOUBLE_EQ(55.340000000000003, v2_.length_squared());
}

TEST_F(Vec3Test, PlusOperator) {
  EXPECT_TRUE((v1_ + v2_) == Vec3(4.2, 6.4, 8.6));
  EXPECT_TRUE((zero_ + zero_) == zero_);
}

TEST_F(Vec3Test, MinusOperator) {
  EXPECT_TRUE((v1_ - v2_) == Vec3(-2.0, -2.0, -2.0));
  EXPECT_TRUE((zero_ - zero_) == zero_);
}

TEST_F(Vec3Test, MultiplicationOperator) {
  EXPECT_TRUE(v1_ * 0 == zero_);
  EXPECT_TRUE(0 * v1_ == zero_);
  EXPECT_TRUE(v2_ * 1 == v2_);
  EXPECT_TRUE(1 * v2_ == v2_);
}

TEST_F(Vec3Test, DivisionOperator) {
  EXPECT_TRUE(zero_ == zero_ / 4.1);
  EXPECT_TRUE(v1_ == v1_ / 1);
  EXPECT_TRUE(Vec3(1.55, 2.1, 2.65) == v2_ / 2);
  EXPECT_TRUE(Vec3(6.2, 8.4, 10.6) == v2_ / 0.5);

  EXPECT_THROW(
      {
        try {
          v1_ / 0.0;
        } catch (std::domain_error const& e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("t is zero; divide by zero exception.", e.what());
          throw;
        }
      },
      std::domain_error);
}

TEST_F(Vec3Test, Equality) {
  EXPECT_TRUE(zero_ == zero_);
  EXPECT_TRUE(v1_ == v1_);
  EXPECT_FALSE(v1_ == v2_);
}

TEST_F(Vec3Test, Inequality) {
  EXPECT_FALSE(zero_ != zero_);
  EXPECT_FALSE(v1_ != v1_);
  EXPECT_TRUE(v1_ != v2_);
}

TEST_F(Vec3Test, Dot) {
  EXPECT_DOUBLE_EQ(30.14, Dot(v1_, v2_));
  EXPECT_DOUBLE_EQ(0, Dot(zero_, v1_));
  EXPECT_DOUBLE_EQ(16.939999999999998, Dot(v1_, v1_));
}

TEST_F(Vec3Test, Cross) {
  EXPECT_TRUE(Vec3(-2.2, 4.4, -2.2) == Cross(v1_, v2_));
  EXPECT_TRUE(Vec3(2.2, -4.4, 2.2) == Cross(v2_, v1_));
  EXPECT_TRUE(zero_ == Cross(v1_, v1_));
}

TEST_F(Vec3Test, UnitVector) {
  EXPECT_TRUE(Vec3(0.2672612419124244, 0.5345224838248488,
                   0.8017837257372732) == UnitVector(v1_));
  EXPECT_TRUE(Vec3(0.41671786217225587, 0.5645854906849919,
                   0.7124531191977277) == UnitVector(v2_));
  EXPECT_THROW(
      {
        try {
          UnitVector(zero_);
        } catch (std::domain_error const& e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("v.length() is zero; divide by zero exception.",
                       e.what());
          throw;
        }
      },
      std::domain_error);
}

TEST_F(Vec3Test, Reflect) {
  EXPECT_TRUE(Vec3(185.768, 250.97600000000003, 316.18399999999997) ==
              Reflect(v1_, v2_));
  EXPECT_TRUE(Vec3(-1, 0, 0) == Reflect(Vec3(1, 0, 0), Vec3(0, 1, 0)));
}

TEST_F(Vec3Test, StreamInsertionOperator) {
  std::ostringstream message_buffer;
  message_buffer << zero_;
  EXPECT_TRUE(message_buffer.str() == "(0, 0, 0)");
  message_buffer = std::ostringstream();
  message_buffer << v1_;
  EXPECT_TRUE(message_buffer.str() == "(1.1, 2.2, 3.3)");
}

}  // namespace
