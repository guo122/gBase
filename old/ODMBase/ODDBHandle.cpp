//====================================================================
//  ODDBHandle.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODDBHandle.h"

ODDBHandle *ODDBHandle::Instance()
{
    static ODDBHandle * obj = new ODDBHandle;
    return obj;
}

ODDBHandle::ODDBHandle()
    : _DBPath("tmp.db")
{

}

ODDBHandle::~ODDBHandle()
{

}

void ODDBHandle::Setup(const std::string &DBPath)
{
    _DBPath = DBPath;
}

bool ODDBHandle::InsertImpl(const ODMBaseList &list, std::string &errMsg)
{
    bool Result = false;
    std::string sql = "";

    std::for_each(list.begin(), list.end(), [&sql](const ODMBasePtr &x){
        x->GetSqlInsert(sql);
    });
    Result = ODSqliteHandle::Exec(_DBPath, sql, errMsg);
    return Result;
}

bool ODDBHandle::UpdateImpl(const ODMBaseList &list, std::string &errMsg)
{
    bool Result = false;
    std::string sql = "";

    std::for_each(list.begin(), list.end(), [&sql](const ODMBasePtr &x){
        x->GetSqlUpdate(sql);
    });
    Result = ODSqliteHandle::Exec(_DBPath, sql, errMsg);
    return Result;
}


