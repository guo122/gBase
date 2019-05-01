//====================================================================
//  gCKK.cpp
//  created 6.13.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include "gBase.h"

#include "gCKK.h"

GZY_NAMESPACE_BEGIN

struct gCKK::Impl
{
    gStringList _classifyList;
    gStringListPtrMap _kindFirstList;
    gMap<gString, gStringListPtrMap> _kindSecondList;
};

gCKK::gCKK()
    : _Impl(new Impl)
{

}

gCKK::~gCKK()
{
    delete _Impl;
}

bool gCKK::append(const gString &classify_, const gString &kindFirst_, const gString &kindSecond_)
{
    bool Result = true;
    gStringListPtr tmpStrListPtr;
    if (classify_.empty() || kindFirst_.empty() || kindSecond_.empty())
    {
        Result = false;
    }
    else
    {
        // classify
        if (gList::RefreshInsert<gString>(_Impl->_classifyList, classify_))
        {
            // classify first appearance
            tmpStrListPtr = gMakeShared<gStringList>();
            tmpStrListPtr->push_back(kindFirst_);
            _Impl->_kindFirstList[classify_] = tmpStrListPtr;

            tmpStrListPtr = gMakeShared<gStringList>();
            tmpStrListPtr->push_back(kindSecond_);
            gStringListPtrMap tmpStrListPtrMap;
            tmpStrListPtrMap[kindFirst_] = tmpStrListPtr;
            _Impl->_kindSecondList[classify_] = tmpStrListPtrMap;
        }
        else
        {
            tmpStrListPtr = _Impl->_kindFirstList[classify_];
            if (gList::RefreshInsert<gString>(*tmpStrListPtr, kindFirst_))
            {
                tmpStrListPtr = gMakeShared<gStringList>();
                tmpStrListPtr->push_back(kindSecond_);
                _Impl->_kindSecondList[classify_][kindFirst_] = tmpStrListPtr;
            }
            else
            {
                tmpStrListPtr = _Impl->_kindSecondList[classify_][kindFirst_];
                gList::RefreshInsert<gString>(*tmpStrListPtr, kindSecond_);
            }
        }
    }
    return Result;
}

bool gCKK::classifyList(gStringList &list)
{
    list = _Impl->_classifyList;
    return !list.empty();
}

bool gCKK::kindFirstList(gStringList &list, const gString &classify_)
{
    bool Result = true;
    gString tmpClassify = classify_;
    gStringListPtr tmpPtr;
    if (classify_.empty() && !_Impl->_classifyList.empty())
    {
        tmpClassify = _Impl->_classifyList[0];
    }
    if (tmpPtr = _Impl->_kindFirstList[tmpClassify])
    {
        list = *tmpPtr;
    }
    else
    {
        list.clear();
        Result = false;
    }
    return Result;
}

bool gCKK::kindSecondList(gStringList &list, const gString &classify_, const gString &kindFirst_)
{
    bool Result = true;
    gString tmpClassify = classify_;
    gString tmpKindFirst = kindFirst_;
    gStringListPtr tmpPtr;
    if (classify_.empty() && !_Impl->_classifyList.empty())
    {
        tmpClassify = _Impl->_classifyList[0];
    }
    if (kindFirst_.empty() && _Impl->_kindFirstList[tmpClassify] && !_Impl->_kindFirstList[tmpClassify]->empty())
    {
        tmpKindFirst = (*(_Impl->_kindFirstList[tmpClassify]))[0];
    }
    if (tmpPtr = _Impl->_kindSecondList[tmpClassify][tmpKindFirst])
    {
        list = *tmpPtr;
    }
    else
    {
        list.clear();
        Result = false;
    }
    return Result;
}

void gCKK::clear()
{
    _Impl->_classifyList.clear();
    _Impl->_kindFirstList.clear();
    _Impl->_kindSecondList.clear();
}

GZY_NAMESPACE_END
