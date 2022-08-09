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
  auto v = find_regex("I am loving Fish1 and Fish2 and Fish99",
                      std::regex("Fish[0-9]"));
  std::vector<std::string> oracle = {"Fish1", "Fish2", "Fish9"};
  EXPECT_EQ(v, oracle);
}

TEST(RegexTest, CaseSensitive)
{
  auto v = find_regex("I am loving Fish1 and Fish2 and Fish99",
                      std::regex("fish[0-9]"));
  std::vector<std::string> oracle;
  EXPECT_EQ(v, oracle);
}