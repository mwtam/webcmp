#include <gtest/gtest.h>
#include "webcmp_tools.h"

// // Demonstrate some basic assertions.
// TEST(HelloTest, BasicAssertions) {
//   // Expect two strings not to be equal.
//   EXPECT_STRNE("hello", "world");
//   // Expect equality.
//   EXPECT_EQ(7 * 6, 42);
// }

TEST(RegexTest, SimpleSearch)
{
  //                   0         1         2         3
  //                   0123456789_123456789_123456789_123456789
  auto v = find_regex("I am loving Fish1 and Fish2 and Fish99",
                      std::regex("Fish[0-9]+"));
  std::vector<std::tuple<int, int>> oracle = {{12,5}, {22,5}, {32,6}};
  EXPECT_EQ(v, oracle);
}

TEST(RegexTest, CaseSensitive)
{
  auto v = find_regex("I am loving Fish1 and Fish2 and Fish99",
                      std::regex("fish[0-9]"));
  std::vector<std::tuple<int, int>> oracle;
  EXPECT_EQ(v, oracle);
}