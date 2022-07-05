//
// Created by ninggyang on 2022/7/1.
//
#include <unordered_map>
#include "gmock/gmock.h"

class Portfolio {
 public:
  using Date = int;
  struct PurchaseRecord {
    Date date;
    int64_t count;
    std::string share;
  };
  using PurchaseRecords = std::vector<PurchaseRecord>;
  bool IsEmpty() {
    return shares_.empty();
  }
  bool Purchase(const std::string &share, uint32_t num, Date date) {
    if (!shares_.count(share)) {
      shares_[share] = 0;
    }
    return ShareChange(share, num, date);
  }

  uint64_t GetShareCount(const std::string &share) {
    return shares_[share];
  }
  PurchaseRecords GetPurchaseRecords() {
    return records_;
  }

  PurchaseRecords GetPurchaseRecords(const std::string &share) {
    return share_records_[share];
  }

  bool Sell(const std::string &share, uint32_t count, Date date) {
    if (!shares_.count(share))
      return false;

    if (count > shares_[share]) {
      return false;
    }
    int64_t shareChange = -1 * static_cast<int64_t>(count);
    ShareChange(share, shareChange, date);
    return true;
  }

 private:
  void UpdateShareCount(const std::string &share, int64_t count) { shares_[share] = count + (int64_t) shares_[share]; }

  void AddPurchaseRecord(const std::string &share, int64_t count, Date date) {
    if (ContainShare(share)) {
      InitPurchaseRecord(share);
    }
    AddRecord(share, count, date);
  }

  bool CheckShareCount(int64_t count) {
    return count != 0;
  }

  bool ShareChange(const std::string &share, int64_t count, Date date) {
    if (!CheckShareCount(count)) {
      return false;
    }
    UpdateShareCount(share, count);
    AddPurchaseRecord(share, count, date);
    return true;
  }

  void AddRecord(const std::string &share, int64_t count, Date date) {
    auto r = PurchaseRecord{date, count, share};
    records_.push_back(r);
    share_records_[share].push_back(r);
  }
  void InitPurchaseRecord(const std::string &share) {
    share_records_[share] = {};
  }
  bool ContainShare(const std::string &share) const { return !share_records_.count(share); }

  std::unordered_map<std::string, uint64_t> shares_;
  PurchaseRecords records_;
  std::unordered_map<std::string, PurchaseRecords> share_records_;
};

class PortfolioTest : public ::testing::Test {
 public:
  bool Purchase(const std::string &share, uint32_t num) {
    return portfolio_.Purchase(share, num, kDefaultDate);
  }

  bool Sell(const std::string &share, uint32_t num) {
    return portfolio_.Sell(share, num, kDefaultDate);
  }
 protected:
  static const std::string kTestShare;

  static const Portfolio::Date kDefaultDate = 0;
  Portfolio portfolio_;
};

const std::string PortfolioTest::kTestShare = "TEST";

TEST_F(PortfolioTest, WhenCreateIsEmpty) {
  ASSERT_THAT(portfolio_.IsEmpty(), testing::Eq(true));
}

TEST_F(PortfolioTest, AfterPurchaseIsNotEmpty) {
  Purchase(kTestShare, 2);
  ASSERT_THAT(portfolio_.IsEmpty(), testing::Eq(false));
}

TEST_F(PortfolioTest, GetShareCount) {
  Purchase(kTestShare, 2);
  ASSERT_THAT(portfolio_.GetShareCount(kTestShare), testing::Eq(2));
}

TEST_F(PortfolioTest, PurchaseSameShare) {
  Purchase(kTestShare, 2);
  ASSERT_THAT(portfolio_.GetShareCount(kTestShare), testing::Eq(2));
  Purchase(kTestShare, 2);
  ASSERT_THAT(portfolio_.GetShareCount(kTestShare), testing::Eq(4));
}

TEST_F(PortfolioTest, PurchaseMulitShare) {
  Purchase("TEST1", 2);
  ASSERT_THAT(portfolio_.GetShareCount("TEST1"), testing::Eq(2));
  Purchase("TEST2", 2);
  ASSERT_THAT(portfolio_.GetShareCount("TEST2"), testing::Eq(2));

  testing::ElementsAre(portfolio_.GetPurchaseRecords(), Portfolio::PurchaseRecord{kDefaultDate, 2, "TEST1"});
  testing::ElementsAre(portfolio_.GetPurchaseRecords(), Portfolio::PurchaseRecord{kDefaultDate, 2, "TEST2"});
}

TEST_F(PortfolioTest, PurchaseMulitTypeShare) {
  Purchase("TEST1", 2);
  ASSERT_THAT(portfolio_.GetShareCount("TEST1"), testing::Eq(2));
  Purchase("TEST2", 2);
  ASSERT_THAT(portfolio_.GetShareCount("TEST2"), testing::Eq(2));

  testing::ElementsAre(portfolio_.GetPurchaseRecords("TEST1"), Portfolio::PurchaseRecord{kDefaultDate, 2, "TEST1"});
  testing::ElementsAre(portfolio_.GetPurchaseRecords("TEST2"), Portfolio::PurchaseRecord{kDefaultDate, 2, "TEST2"});
}

TEST_F(PortfolioTest, PurchaseRecordsNotFind) {
  Purchase("TEST1", 2);
  ASSERT_THAT(portfolio_.GetShareCount("TEST1"), testing::Eq(2));
  Purchase("TEST2", 2);
  ASSERT_THAT(portfolio_.GetShareCount("TEST2"), testing::Eq(2));

  testing::ElementsAre(portfolio_.GetPurchaseRecords("TEST3").empty(), testing::Eq(true));
}

TEST_F(PortfolioTest, PurchaseZeroShare) {
  ASSERT_THAT(Purchase(kTestShare, 0), testing::Eq(false));
}

TEST_F(PortfolioTest, SellShare) {
  bool res = Sell(kTestShare, 2);
  ASSERT_THAT(res, testing::Eq(false));
  Purchase(kTestShare, 2);
  ASSERT_THAT(Sell(kTestShare, 2), testing::Eq(true));
  ASSERT_THAT(portfolio_.GetShareCount(kTestShare), testing::Eq(0));
}

TEST_F(PortfolioTest, GetPurchaseRecord) {
  auto records = portfolio_.GetPurchaseRecords();
  ASSERT_THAT(records.empty(), testing::Eq(true));

  portfolio_.Purchase(kTestShare, 2, 2);
  records = portfolio_.GetPurchaseRecords();
  ASSERT_THAT(records.empty(), testing::Eq(false));

  ASSERT_THAT(records[0].share, testing::Eq(kTestShare));
  ASSERT_THAT(records[0].count, testing::Eq(2));
  ASSERT_THAT(records[0].date, testing::Eq(2));
}