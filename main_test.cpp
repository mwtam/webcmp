#include <gtest/gtest.h>
#include "webcmp_tools.h"

TEST(SearchRegExRetStrV, SimpleSearch)
{
  std::string s = "I am loving Fish1 and Fish2 and Fish99";
  auto v = search_regex_str_v(s, std::regex("Fish[0-9]+"));
  std::vector<std::string_view> oracle = {"Fish1", "Fish2", "Fish99"};
  EXPECT_EQ(v, oracle);
}

TEST(SearchRegExRetStrV, SimpleSearchChar)
{
  auto v = search_regex_str_v(
      "I am loving Fish1 and Fish2 and Fish99",
      std::regex("Fish[0-9]+"));
  std::vector<std::string_view> oracle = {"Fish1", "Fish2", "Fish99"};
  EXPECT_EQ(v, oracle);
}

TEST(SearchRegExRetStrV, CaseSensitive)
{
  std::string s = "I am loving Fish1 and Fish2 and Fish99";
  auto v = search_regex_str_v(s, std::regex("fish[0-9]+"));
  std::vector<std::string_view> oracle;
  EXPECT_EQ(v, oracle);
}

// TEST(SearchRegExRetStrV, BadUse)
// {
//   // This should fail to compile
//   auto v = search_regex_str_v("I am loving Fish1 and Fish2 and Fish99", std::regex("Fish[0-9]+"));
//   std::vector<std::string_view> oracle = {"Fish1", "Fish2", "Fish99"};
//   EXPECT_EQ(v, oracle);
// }

TEST(SearchRegExRetStrV, Normalize_Result)
{
  std::string s = "I am loving Fish07 and Fish02 and Fish29 and Fish02";
  auto v = search_regex_str_v(s, std::regex("Fish[0-9]+"));
  std::vector<std::string_view> oracle_01 = {"Fish07", "Fish02", "Fish29", "Fish02"};
  EXPECT_EQ(v, oracle_01);

  normalize_result(v);
  std::vector<std::string_view> oracle_02 = {"Fish02", "Fish07", "Fish29"};
  EXPECT_EQ(v, oracle_02);
}