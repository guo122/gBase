//====================================================================
//  gCKK_test.cpp
//  created 6.13.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <gtest/gtest.h>

#include <gBase/gCKK.h>

TEST(gCKK, ToString)
{
    gzy::gCKKPtr ckk = std::make_shared<gzy::gCKK>();
//    CKKPtr ckk;
    ckk.reset();
    ckk = std::make_shared<gzy::gCKK>();
    EXPECT_TRUE(ckk->append("1", "11", "111"));
    EXPECT_TRUE(ckk->append("1", "11", "112"));
    EXPECT_TRUE(ckk->append("1", "12", "121"));
    EXPECT_TRUE(ckk->append("1", "13", "131"));
    EXPECT_TRUE(ckk->append("2", "21", "211"));
    EXPECT_TRUE(ckk->append("2", "22", "221"));
    EXPECT_TRUE(ckk->append("2", "23", "231"));
    EXPECT_TRUE(ckk->append("3", "31", "311"));

    gzy::gStringList tmpList;
    EXPECT_TRUE(ckk->classifyList(tmpList));
    EXPECT_EQ(tmpList.size(), 3);
    
    EXPECT_TRUE(ckk->kindFirstList(tmpList, "1"));
    EXPECT_TRUE(ckk->kindFirstList(tmpList, "2"));
    EXPECT_TRUE(ckk->kindFirstList(tmpList, "3"));
    
    EXPECT_FALSE(ckk->kindFirstList(tmpList, "4"));
    
    EXPECT_TRUE(ckk->kindSecondList(tmpList, "1", "11"));
    EXPECT_TRUE(ckk->kindSecondList(tmpList, "1", "13"));
    EXPECT_TRUE(ckk->kindSecondList(tmpList, "2", "21"));
    EXPECT_TRUE(ckk->kindSecondList(tmpList, "3", "31"));
    EXPECT_FALSE(ckk->kindSecondList(tmpList, "3", "32"));
    
    EXPECT_TRUE(ckk->kindFirstList(tmpList));
    EXPECT_TRUE(ckk->kindSecondList(tmpList, "2"));
    EXPECT_TRUE(ckk->kindSecondList(tmpList));
}
