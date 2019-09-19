//====================================================================
//  gStringUtil.cpp
//  created 9.18.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include "gStringUtil.h"

GZY_NAMESPACE_BEGIN

gStringUtil::gStringUtil()
{

}

gStringSplit::gStringSplit( gString* InStr, const gString& token )
	: m_Str( InStr )
	, m_Token( token )
{
	m_tokenSize = m_Token.size();
	m_pos2 = m_Str->find( m_Token );
	m_next = m_Str->substr( m_pos1, m_pos2 - m_pos1 );
}

gString gStringSplit::next()
{
	gString ret = m_next;

	if ( !m_Token.empty() )
	{
		m_pos1 = m_pos2 + m_tokenSize;
		m_pos2 = m_Str->find( m_Token, m_pos1 );
		m_next = m_Str->substr( m_pos1, m_pos2 - m_pos1 );

		if ( m_pos2 == gString_npos )
		{
			m_Token = "";
		}
	}
	else
	{
		m_next = "";
	}

	return ret;
}

GZY_NAMESPACE_END
