//====================================================================
//  ODCKK.cpp
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODCKK.h"
#include "ODUtil.h"

struct ODCKK::Impl
{
    StringList _classifyList;
    StringListPtrMap _kindFirstList;
    std::map<std::string, StringListPtrMap> _kindSecondList;
};

ODCKK::ODCKK()
    : _Impl(new Impl)
{

}

ODCKK::~ODCKK()
{
    delete _Impl;
}

bool ODCKK::appendData(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_)
{
    bool Result = true;
    StringListPtr tmpStrListPtr;
    if (classify_.empty() || kindFirst_.empty() || kindSecond_.empty())
    {
        Result = false;
    }
    else
    {
        // classify
        if (ODVectorUtil::RefreshInsert<std::string>(_Impl->_classifyList, classify_))
        {
            // classify first appearance
            tmpStrListPtr = std::make_shared<StringList>();
            tmpStrListPtr->push_back(kindFirst_);
            _Impl->_kindFirstList[classify_] = tmpStrListPtr;

            tmpStrListPtr = std::make_shared<StringList>();
            tmpStrListPtr->push_back(kindSecond_);
            StringListPtrMap tmpStrListPtrMap;
            tmpStrListPtrMap[kindFirst_] = tmpStrListPtr;
            _Impl->_kindSecondList[classify_] = tmpStrListPtrMap;
        }
        else
        {
            tmpStrListPtr = _Impl->_kindFirstList[classify_];
            if (ODVectorUtil::RefreshInsert<std::string>(*tmpStrListPtr, kindFirst_))
            {
                tmpStrListPtr = std::make_shared<StringList>();
                tmpStrListPtr->push_back(kindSecond_);
                _Impl->_kindSecondList[classify_][kindFirst_] = tmpStrListPtr;
            }
            else
            {
                tmpStrListPtr = _Impl->_kindSecondList[classify_][kindFirst_];
                ODVectorUtil::RefreshInsert<std::string>(*tmpStrListPtr, kindSecond_);
            }
        }
    }
    return Result;
}

bool ODCKK::classifyList(StringList &list)
{
    list = _Impl->_classifyList;
    return !list.empty();
}

bool ODCKK::kindFirstList(StringList &list, const std::string &classify_)
{
    bool Result = true;
    std::string tmpClassify = classify_;
    StringListPtr tmpPtr;
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

bool ODCKK::kindSecondList(StringList &list, const std::string &classify_, const std::string &kindFirst_)
{
    bool Result = true;
    std::string tmpClassify = classify_;
    std::string tmpKindFirst = kindFirst_;
    StringListPtr tmpPtr;
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

void ODCKK::clear()
{
    _Impl->_classifyList.clear();
    _Impl->_kindFirstList.clear();
    _Impl->_kindSecondList.clear();
}
