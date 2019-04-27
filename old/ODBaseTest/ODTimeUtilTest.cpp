//====================================================================
//  ODTimeUtilTest.cpp
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>

#include <ODUtil/ODTimeUtil.h>

//TEST(ODTimeUtil, ToString)
//{
//    std::string tmpStr;
//    tmpStr = ODTimeUtil::Timestamp2String(1528184066, "%y%m%d_%H%M%S");
//    EXPECT_EQ("180605_153426", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(1528184066, "%dDays %2Hhour %2MMinute %2SSecond");
//    EXPECT_EQ("17687Days 07hour 34Minute 26Second", tmpStr);
//}

//TEST(ODTimeUtil, IsSameDay)
//{
//    EXPECT_TRUE(ODTimeUtil::IsSameDay(1528192338, 1528192339));
//    EXPECT_TRUE(ODTimeUtil::IsSameDay(1528192338, 1528195000));
//    EXPECT_TRUE(ODTimeUtil::IsSameDay(1528192338, 1528199000));
//    EXPECT_TRUE(ODTimeUtil::IsSameDay(1528128000, 1528128001));
//    EXPECT_FALSE(ODTimeUtil::IsSameDay(1528128000, 1528127999));
//}

//TEST(ODTimeUtil, Duration2Str)
//{
//    std::string tmpStr;
//    tmpStr = ODTimeUtil::Duration2String(12);
//    EXPECT_EQ("12s", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(72);
//    EXPECT_EQ("01m", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(1002);
//    EXPECT_EQ("16m", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(3002);
//    EXPECT_EQ("50m", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(7002);
//    EXPECT_EQ("1h56m", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(27002);
//    EXPECT_EQ("7h30m", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(227002);
//    EXPECT_EQ("2d 15h03m", tmpStr);

//    tmpStr = ODTimeUtil::Duration2String(12, "__DIGITAL__");
//    EXPECT_EQ("00:00:12", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(72, "__DIGITAL__");
//    EXPECT_EQ("00:01:12", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(1002, "__DIGITAL__");
//    EXPECT_EQ("00:16:42", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(3002, "__DIGITAL__");
//    EXPECT_EQ("00:50:02", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(7002, "__DIGITAL__");
//    EXPECT_EQ("01:56:42", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(27002, "__DIGITAL__");
//    EXPECT_EQ("07:30:02", tmpStr);
//    tmpStr = ODTimeUtil::Duration2String(227002, "__DIGITAL__");
//    EXPECT_EQ("2-15:03:22", tmpStr);
//}

//TEST(ODTimeUtil, DateJump)
//{
//    std::string tmpStr = "18-01-22";
//    ODTimeUtil::DateJump(tmpStr, -7);
//    EXPECT_EQ("18-01-15", tmpStr);

//    tmpStr = "18-02-22";
//    ODTimeUtil::DateJump(tmpStr, -7);
//    EXPECT_EQ("18-02-15", tmpStr);

//    tmpStr = "17-02-28";
//    ODTimeUtil::DateJump(tmpStr, -7);
//    EXPECT_EQ("17-02-21", tmpStr);

//    tmpStr = "17-01-01";
//    ODTimeUtil::DateJump(tmpStr, -7);
//    EXPECT_EQ("16-12-25", tmpStr);

//    tmpStr = "18-12-31";
//    ODTimeUtil::DateJump(tmpStr, 7);
//    EXPECT_EQ("19-01-07", tmpStr);

//    tmpStr = "17-02-28";
//    ODTimeUtil::DateJump(tmpStr, 30);
//    EXPECT_EQ("17-03-30", tmpStr);
//}

//TEST(ODTimeUtil, CalBillList)
//{
//    int index;
//    std::string tmpStr;
//    EXPECT_TRUE(ODTimeUtil::CalBillList(1514736000, 10, index, tmpStr));
//    std::cout << "20180101: " << index << std::endl;
//    EXPECT_TRUE(ODTimeUtil::CalBillList(1517414400, 10, index, tmpStr));
//    std::cout << "20180201: " << index << std::endl;
//}
