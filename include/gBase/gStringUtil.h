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
	gStringSplit( const gString& InStr, const gString& token = " " );

public:
	gString		next();
	void		clear();

private:
	gString_sizetype	m_pos1{ 0 };
	gString_sizetype	m_pos2{ gString_npos };
	gString_sizetype	m_len{ gString_npos };
	gString_sizetype	m_tokenSize{ gString_npos };
	gString				m_Str{ "" };
	gString				m_Token{ " " };
	gString				m_next{ "" };
};

GZY_NAMESPACE_END

#endif // GSTRINGUTIL_H_DF86C1FFA8DD4AA936D797FD458AD395
