//
// Created by ninggyang on 2022/6/9.
//

#ifndef TDD_APP__SOUNDEX_H_
#define TDD_APP__SOUNDEX_H_

#include <string>
#include <unordered_map>
class Soundex {
 public:
  std::string encode(const std::string &w) {
    return paddingZero(head(w) + encodeDigits(w));
  }

 private:
  std::string head(const std::string &w) const {
    if (w.empty()) return "";
    return std::string(1, static_cast<char >(std::toupper(w.front())));
  }

  std::string lastLetterEncoding(const std::string &encode) {
    return encode.empty() ? "" : std::string(1, encode.back());
  }

  std::string encodeDigits(const std::string &w) {
    std::string res;
    encodeHead(w, res);
    encodeTail(w, res);
    return res;
  }
  void encodeTail(const std::string &w, std::string &res) {
    for (int i = 2; i < w.size(); ++i) {
      if (isComplete(res)) break;
      encodeLetter(w[i], res);
    }
  }
  void encodeLetter(char c, std::string &res) {
    auto encode = encodeDigit(c);
    if (!encode.empty() && encode != lastLetterEncoding(res)) {
      res.append(encode);
    }
  }
  void encodeHead(const std::string &w, std::string &res) {
    if (w.size() >= 2) {
      if (encodeDigit(w[0]) != encodeDigit(w[1])) {
        res.append(encodeDigit(w[1]));
      }
    }
  }

  bool isComplete(const std::string &res) const { return res.length() == kMaxCodeLength - 1; }

  std::string encodeDigit(char c) {
    c = static_cast<char >(tolower(c));
    std::unordered_map<char, std::string> c2digit{
        {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
        {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"},
        {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
        {'d', "3"}, {'t', "3"}, {'l', "4"},
        {'m', "5"}, {'n', "5"}, {'r', "6"}};
    return c2digit[c];
  }

  static const int kMaxCodeLength = 4;
  std::string paddingZero(const std::string &w) {
    if (w.size() < kMaxCodeLength) {
      return w + std::string(kMaxCodeLength - w.size(), '0');
    }
    return w;
  }

};

#endif //TDD_APP__SOUNDEX_H_
