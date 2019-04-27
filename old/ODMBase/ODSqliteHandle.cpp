//====================================================================
//  ODSqliteHandle.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <sqlite3.h>

#include "ODSqliteHandle.h"

static int callback(void *PV, int argc, char **argv, char **azColName)
{
    StringTable * stringTable = reinterpret_cast<StringTable *>(PV);
    StringList tmpList;

//    if (stringTable->empty())
//    {
//        for (int i = 0; i < argc; ++i)
//        {
//            tmpList.push_back(azColName[i]);
//        }
//        stringTable->push_back(tmpList);
//        tmpList.clear();
//    }

    for (int i = 0; i < argc; ++i)
    {
        if (argv[i])
        {
            tmpList.push_back(argv[i]);
        }
        else
        {
            tmpList.push_back("");
        }
    }
    stringTable->push_back(tmpList);

    return 0;
}

ODSqliteHandle::ODSqliteHandle()
{

}

bool ODSqliteHandle::ExecImpl(
        const std::string &DBPath,
        const std::string &Sql,
        StringTable &ResStringTable,
        std::string &ErrMsg)
{
    bool Result = true;
    sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;

    /* Open database */
    rc = sqlite3_open(DBPath.c_str(), &db);
    if(rc)
    {
        ErrMsg = "Can't open database: ";
        ErrMsg += sqlite3_errmsg(db);
        Result = false;
    }
    else
    {
        /* Execute SQL statement */
        rc = sqlite3_exec(db, Sql.c_str(), callback, &ResStringTable, &zErrMsg);
        if(rc != SQLITE_OK)
        {
            ErrMsg = "SQL error: ";
            ErrMsg += zErrMsg;
            Result = false;
        }
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
    }
    return Result;
}
