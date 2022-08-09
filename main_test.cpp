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
  std::string s = "I am loving Fish1 and Fish2 and Fish99";
  auto v = find_regex(s, std::regex("Fish[0-9]+"));
  std::vector<std::string_view> oracle = {"Fish1", "Fish2", "Fish99"};
  EXPECT_EQ(v, oracle);
}

TEST(RegexTest, CaseSensitive)
{
  auto v = find_regex("I am loving Fish1 and Fish2 and Fish99",
                      std::regex("fish[0-9]"));
  std::vector<std::string_view> oracle;
  EXPECT_EQ(v, oracle);
}