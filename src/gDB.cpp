//====================================================================
//  gDB.cpp
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include "gDB.h"

GZY_NAMESPACE_BEGIN

gDB *gDB::Instance()
{
    static gDB * obj = new gDB;
    return obj;
}

gDB::gDB()
    : _DBPath("tmp.db")
{

}

gDB::~gDB()
{

}

void gDB::Setup(const gString &DBPath)
{
    _DBPath = DBPath;
}

bool gDB::InsertImpl(const gMBaseList &list, gString &errMsg)
{
    bool Result = false;
    gString sql = "";

    gForeach(list.begin(), list.end(), [&sql](const gMBasePtr &x){
        x->GetSqlInsert(sql);
    });
    Result = gSqlite::Exec(_DBPath, sql, errMsg);
    return Result;
}

bool gDB::UpdateImpl(const gMBaseList &list, gString &errMsg)
{
    bool Result = false;
    gString sql = "";

    gForeach(list.begin(), list.end(), [&sql](const gMBasePtr &x){
        x->GetSqlUpdate(sql);
    });
    Result = gSqlite::Exec(_DBPath, sql, errMsg);
    return Result;
}

GZY_NAMESPACE_END
