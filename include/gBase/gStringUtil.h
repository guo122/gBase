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

class gStringSplit
{
public:
	gStringSplit( gString* InStr, const gString& token = " " );

public:
	gString		next();

private:
    gString*            m_Str{ nullptr };
    gString             m_Token{ " " };
    gString             m_next{ "" };
	gString_sizetype	m_pos1{ 0 };
	gString_sizetype	m_pos2{ gString_npos };
	gString_sizetype	m_tokenSize{ gString_npos };
};

GZY_NAMESPACE_END

#endif // GSTRINGUTIL_H_DF86C1FFA8DD4AA936D797FD458AD395
