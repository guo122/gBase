//====================================================================
//  gDB.h
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GDB_H_DB81DA8B00554332D1F1E565FEAE9A99
#define GDB_H_DB81DA8B00554332D1F1E565FEAE9A99

#include "defines.h"
#include "gSqlite.h"

GZY_NAMESPACE_BEGIN

struct gMBase
{
public:
    gMBase(const int &id_): _preId(id_), _id(id_), _type("gMBase"){}
    gMBase(const gString &type_): _type(type_)
    {
        //todo
        time_t curTime = 0;
        _preId = _id = time(&curTime);
    }
    gMBase(const gString &type_, const int &id_): _preId(id_), _id(id_), _type(type_){}
    
public:
    // The following 5 function must implementation.
    static void GetSqlCreateTable(gString &sql_){}
    static void GetSqlSelect(gString &sql_){}
    static void GetSqlDelete(gString &sql_, const int &id_){}
    virtual void GetSqlInsert(gString &sql_) = 0;
    virtual void GetSqlUpdate(gString &sql_) = 0;
    
public:
    int _preId;
    int _id;
    gString _type;
};
typedef gSharedPtr<gMBase> gMBasePtr;
typedef gVector<gMBasePtr> gMBaseList;

/**
 * @brief The gDB class
 *  基于gMBase数据类型的sqlite快速使用工具类
 *  已实现 Select、Insert、Delete、Update
 */

class gDB
{
public:
    static gDB * Instance();

public:
    void Setup(const gString &DBPath);

public:
    template<class T>
    bool Select(gMBaseList &list)
    {
        gString errMsg;
        return SelectImpl<T>(list, errMsg);
    }

    template<class T>
    bool Select(gMBaseList &list, gString &errMsg)
    {
        return SelectImpl<T>(list, errMsg);
    }

    template<class T>
    bool Delete(const gIntList &list)
    {
        gString errMsg;
        return DeleteImpl<T>(list, errMsg);
    }

    template<class T>
    bool Delete(const gIntList &list, gString &errMsg)
    {
        return DeleteImpl<T>(list, errMsg);
    }

    bool Insert(const gMBaseList &list)
    {
        gString errMsg;
        return InsertImpl(list, errMsg);
    }
    bool Insert(const gMBaseList &list, gString &errMsg)
    {
        return InsertImpl(list, errMsg);
    }

    bool Update(const gMBaseList &list)
    {
        gString errMsg;
        return UpdateImpl(list, errMsg);
    }
    bool Update(const gMBaseList &list, gString &errMsg)
    {
        return UpdateImpl(list, errMsg);
    }

private:
    template<class T>
    bool SelectImpl(gMBaseList &list, gString &errMsg)
    {
        bool Result = false;
        gStringTable gStringTable;
        gString sql = "";
        T::GetSqlSelect(sql);
        Result = gSqlite::Exec(_DBPath, sql, gStringTable, errMsg);

        gForeach(gStringTable.begin(), gStringTable.end(), [&list](gStringList &x){
            list.push_back(gMakeShared<T>(x));
        });
        return Result;
    }

    template<class T>
    bool DeleteImpl(const gIntList &list, gString &errMsg)
    {
        bool Result = false;
        gString sql = "";

        gForeach(list.begin(), list.end(), [&sql](const int &x){
            T::GetSqlDelete(sql, x);
        });
        Result = gSqlite::Exec(_DBPath, sql, errMsg);
        return Result;
    }

    bool InsertImpl(const gMBaseList &list, gString &errMsg);

    bool UpdateImpl(const gMBaseList &list, gString &errMsg);
private:
    gDB();
    ~gDB();

private:
    gString _DBPath;
};

GZY_NAMESPACE_END

#endif // GDB_H_DB81DA8B00554332D1F1E565FEAE9A99
