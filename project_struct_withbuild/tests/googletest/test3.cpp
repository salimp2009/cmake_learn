#include "sort.hpp"
#include <cassert>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <print.hpp>
int main(int argc, char **argv) {
  // Creating and Running Tests Chapter 4 [160]
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(sortTest, test_sample) {
  std::vector<double> integers = {1, -1, 2, -3};
  mySort(integers);
  ASSERT_EQ(integers[0], -3);
  ASSERT_THAT(integers, testing::ElementsAre(-3, -1, 1, 2));
  // assert(integers[0] == -3);
}
