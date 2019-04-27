//====================================================================
//  ODSqliteHandle_test.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>
#include <ODMBase/ODMTest.h>
#include <ODMBase/ODDBHandle.h>

StringTable testStrTable = {
    {"12", "vvasdf", "43"},
    {"32", "lgasdf", "34"}
};



//TEST(ODSqliteHandle, exec)
//{
//    ODMBaseList tmpList;
//    ODDBHandle::Instance()->Setup("test.db");
//    ODDBHandle::Instance()->Select<ODMTest>(tmpList);
//    ODMTestPtr tmpPtr = std::static_pointer_cast<ODMTest>(tmpList[0]);
//    ODMTestPtr tmpA = std::make_shared<ODMTest>();
//    std::cout << "asd" << std::endl;
//}

//TEST(ODDBHandle, insert)
//{
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMTest>(testStrTable[0]));
//    tmpList.push_back(std::make_shared<ODMTest>(testStrTable[1]));
//    ODDBHandle::Instance()->Insert(tmpList);
//}

//TEST(ODDBHandle, Update)
//{
//    ODDBHandle::Instance()->Setup("test.db");
//    ODMBaseList tmpList;
//    std::string tmpStr;
//    tmpList.push_back(std::make_shared<ODMTest>(testStrTable[0]));
//    tmpList.push_back(std::make_shared<ODMTest>(testStrTable[1]));
//    ODMTestPtr tmpPtr = std::static_pointer_cast<ODMTest>(tmpList[0]);
//    tmpPtr->_name = "changeNew12";
//    tmpPtr->_score = 122;
//    tmpPtr = std::static_pointer_cast<ODMTest>(tmpList[1]);
//    tmpPtr->_name = "changeNew32";
//    tmpPtr->_score = 322;
//    ODDBHandle::Instance()->Update(tmpList, tmpStr);
//    std::cout << tmpStr << std::endl;
//}

//TEST(ODDBHandle, Delete)
//{
//    IntList tmpList = {1, 3, 32};
//    std::string tmpStr;
//    ODDBHandle::Instance()->Delete<ODMTest>(tmpList, tmpStr);
//}
