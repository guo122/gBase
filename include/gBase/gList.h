//====================================================================
//  gList.h
//  created 6.5.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GLIST_H_DE49445E42C90D27825ACC797D37ECF4
#define GLIST_H_DE49445E42C90D27825ACC797D37ECF4

#include "defines.h"

GZY_NAMESPACE_BEGIN

class gList
{
public:
    gList();

public:
    template<typename T>
    static bool RefreshInsert(gVector<T> &list_, const T &val_)
    {
        bool Result = true;
        for (auto pos = list_.begin(); pos != list_.end(); ++pos)
        {
            if ((*pos) == val_)
            {
                list_.erase(pos);
                Result = false;
                break;
            }
        }
        list_.insert(list_.begin(), val_);
        return Result;
    }
};

GZY_NAMESPACE_END

#endif // GLIST_H_DE49445E42C90D27825ACC797D37ECF4
