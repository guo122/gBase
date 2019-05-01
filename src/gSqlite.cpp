//====================================================================
//  gSqlite.cpp
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <sqlite3.h>

#include "gSqlite.h"

GZY_NAMESPACE_BEGIN

static int callback(void *PV, int argc, char **argv, char **azColName)
{
    gStringTable * gStringTable = reinterpret_cast<::gzy::gStringTable *>(PV);
    gStringList tmpList;

//    if (gStringTable->empty())
//    {
//        for (int i = 0; i < argc; ++i)
//        {
//            tmpList.push_back(azColName[i]);
//        }
//        gStringTable->push_back(tmpList);
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
    gStringTable->push_back(tmpList);

    return 0;
}

gSqlite::gSqlite()
{

}

bool gSqlite::ExecImpl(
        const gString &DBPath,
        const gString &Sql,
        gStringTable &ResgStringTable,
        gString &ErrMsg)
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
        rc = sqlite3_exec(db, Sql.c_str(), callback, &ResgStringTable, &zErrMsg);
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

GZY_NAMESPACE_END
