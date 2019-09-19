//====================================================================
//  gStringUtil.h
//  created 9.18.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GSTRINGUTIL_H_DF86C1FFA8DD4AA936D797FD458AD395
#define GSTRINGUTIL_H_DF86C1FFA8DD4AA936D797FD458AD395

#include "defines.h"

GZY_NAMESPACE_BEGIN

class gStringUtil
{
public:
	gStringUtil();

public:

};

class ISplit
{
public:
    ISplit()
    : m_Str(nullptr)
    , m_pos1(0)
    , m_pos2(gString_npos)
    {}
    ~ISplit(){}
    
public:
    virtual gString     next() = 0;
    bool                end() { return m_Str == nullptr; }
    
protected:
    gString*            m_Str;
    gString_sizetype    m_pos1;
    gString_sizetype    m_pos2;
};

class gSplit : public ISplit
{
public:
    gSplit( gString* InStr, const gString& token = " " );

public:
	virtual gString		next();
    int         next_i();
    float       next_f();
    
private:
    gString             m_Token;
    gString             m_next;
    gString_sizetype    m_tokenSize;
};

class gSplitArray : public ISplit
{
public:
    gSplitArray( gString* InStr );
    
public:
    virtual gString     next();
};

GZY_NAMESPACE_END

#endif // GSTRINGUTIL_H_DF86C1FFA8DD4AA936D797FD458AD395
