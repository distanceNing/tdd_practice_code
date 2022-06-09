//
// Created by ninggyang on 2022/6/9.
//

#include "gtest/gtest.h"
#include "soundex.h"

class SoundexTest : public testing::Test {
 protected:
  Soundex soundex;
};

TEST_F(SoundexTest, OneLetter) {
  ASSERT_EQ(soundex.encode("x"), "X000");
}

TEST_F(SoundexTest, PadWithZero) {
  ASSERT_EQ(soundex.encode("x"), "X000");
  ASSERT_EQ(soundex.encode(""), "0000");
}

TEST_F(SoundexTest, ConsonantReplaceWithDigital) {
  ASSERT_EQ(soundex.encode("Ab"), "A100");
  ASSERT_EQ(soundex.encode("Ac"), "A200");
  ASSERT_EQ(soundex.encode("Ad"), "A300");
  ASSERT_EQ(soundex.encode("Ae"), "A000");
}

TEST_F(SoundexTest, ReplaceMultipleConsonantWithDigital) {
  ASSERT_EQ(soundex.encode("Abcl"), "A124");
  ASSERT_EQ(soundex.encode("Acdl"), "A234");
}

TEST_F(SoundexTest, LimitLength) {
  ASSERT_EQ(soundex.encode("Abclfe").size(), 4);
}

TEST_F(SoundexTest, CombineSameLetter) {
  ASSERT_EQ(soundex.encode("Abfcgdt"), "A123");
}

TEST_F(SoundexTest, FirstLetterUpper) {
  ASSERT_EQ(soundex.encode("abfc"), "A120");
}

TEST_F(SoundexTest, IgnoreCase) {
  ASSERT_EQ(soundex.encode("Abfc"), soundex.encode("ABFC"));
}

TEST_F(SoundexTest, CombineLetterWhen2ndletterSameTo1st) {
  ASSERT_EQ(soundex.encode("Bbcd"), "B230");
}
