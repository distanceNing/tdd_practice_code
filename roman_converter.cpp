//
// Created by ninggyang on 2022/6/10.
//

#include <unordered_map>
#include "gmock/gmock.h"
#include "roman_converter.h"

using namespace testing;

class RomanConverter {
 public:
  std::string convert(int num) {
    std::string res;

    const std::pair<int, std::string> digit2RomanMap[] = {
        std::make_pair(1000, "M"),
        std::make_pair(500, "D"),
        std::make_pair(100, "C"),
        std::make_pair(50, "L"),
        std::make_pair(10, "X"),
        std::make_pair(5, "V"),
        std::make_pair(4, "IV"),
        std::make_pair(1, "I")};

    for (const auto &p: digit2RomanMap) {
      while (num >= p.first) {
        res.append(p.second);
        num -= p.first;
      }
    }
    return res;
  }
};

class RomanConverterTest : public Test {
 protected:
  RomanConverter converter_;
};

TEST_F(RomanConverterTest, Convert) {
  ASSERT_THAT(converter_.convert(1), Eq("I"));
  ASSERT_THAT(converter_.convert(2), Eq("II"));
  ASSERT_THAT(converter_.convert(3), Eq("III"));

  ASSERT_THAT(converter_.convert(4), Eq("IV"));
  ASSERT_THAT(converter_.convert(5), Eq("V"));

  ASSERT_THAT(converter_.convert(10), Eq("X"));

  ASSERT_THAT(converter_.convert(11), Eq("XI"));

  ASSERT_THAT(converter_.convert(20), Eq("XX"));
  ASSERT_THAT(converter_.convert(21), Eq("XXI"));

  ASSERT_THAT(converter_.convert(50), Eq("L"));
  ASSERT_THAT(converter_.convert(100), Eq("C"));
  ASSERT_THAT(converter_.convert(500), Eq("D"));
  ASSERT_THAT(converter_.convert(1000), Eq("M"));
}