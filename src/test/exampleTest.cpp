#include "gtest/gtest.h"

class ExampleTest : public ::testing::Test {
};

TEST_F(ExampleTest, CheckAssertion) {
  ASSERT_EQ(1, 1);
} 