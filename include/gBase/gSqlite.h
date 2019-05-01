//====================================================================
//  gSqlite.h
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GSQLITE_H_6BC0E607E9DCA3298DCD458978C18C34
#define GSQLITE_H_6BC0E607E9DCA3298DCD458978C18C34

#include "defines.h"

GZY_NAMESPACE_BEGIN

class gSqlite
{
public:
    gSqlite();

public:
    static bool Exec(
            const gString &DBPath,
            const gString &Sql,
            gStringTable &ResgStringTable,
            gString &ErrMsg)
    {
        return ExecImpl(DBPath, Sql, ResgStringTable, ErrMsg);
    }

    static bool Exec(
            const gString &DBPath,
            const gString &Sql,
            gString &ErrMsg)
    {
        gStringTable gStringTable;
        return ExecImpl(DBPath, Sql, gStringTable, ErrMsg);
    }

private:
    static bool ExecImpl(
            const gString &DBPath,
            const gString &Sql,
            gStringTable &ResgStringTable,
            gString &ErrMsg);
};

GZY_NAMESPACE_END

#endif // GSQLITE_H_6BC0E607E9DCA3298DCD458978C18C34
