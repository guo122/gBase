//====================================================================
//  ODCKKTest.cpp
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>

#include <ODUtil/ODCKK.h>

//TEST(ODCKK, ToString)
//{
//    CKKPtr ckk = std::make_shared<ODCKK>();
////    CKKPtr ckk;
//    ckk.reset();
//    ckk = std::make_shared<ODCKK>();
//    EXPECT_TRUE(ckk->appendData("1", "11", "111"));
//    EXPECT_TRUE(ckk->appendData("1", "11", "112"));
//    EXPECT_TRUE(ckk->appendData("1", "12", "121"));
//    EXPECT_TRUE(ckk->appendData("1", "13", "131"));
//    EXPECT_TRUE(ckk->appendData("2", "21", "211"));
//    EXPECT_TRUE(ckk->appendData("2", "22", "221"));
//    EXPECT_TRUE(ckk->appendData("2", "23", "231"));
//    EXPECT_TRUE(ckk->appendData("3", "31", "311"));

//    StringList tmpList;
//    EXPECT_TRUE(ckk->classifyList(tmpList));
//    EXPECT_EQ(tmpList.size(), 2);
//    EXPECT_TRUE(ckk->kindFirstList(tmpList, "1"));
//    EXPECT_TRUE(ckk->kindFirstList(tmpList, "2"));
//    EXPECT_TRUE(ckk->kindFirstList(tmpList, "3"));
//    EXPECT_FALSE(ckk->kindFirstList(tmpList, "4"));
//    EXPECT_TRUE(ckk->kindSecondList(tmpList, "1", "11"));
//    EXPECT_TRUE(ckk->kindSecondList(tmpList, "1", "13"));
//    EXPECT_TRUE(ckk->kindSecondList(tmpList, "2", "21"));
//    EXPECT_TRUE(ckk->kindSecondList(tmpList, "3", "31"));
//    EXPECT_FALSE(ckk->kindSecondList(tmpList, "3", "32"));
//    EXPECT_TRUE(ckk->kindFirstList(tmpList));
//    EXPECT_TRUE(ckk->kindSecondList(tmpList, "2"));
//    EXPECT_TRUE(ckk->kindSecondList(tmpList));
//}
