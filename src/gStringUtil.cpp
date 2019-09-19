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

gSplit::gSplit( gString* InStr, const gString& token )
{
    m_Str = InStr;
    m_Token = token;
	m_tokenSize = m_Token.size();
    m_pos1 = 0;
	m_pos2 = m_Str->find( m_Token );
	m_next = m_Str->substr( m_pos1, m_pos2 - m_pos1 );
}

gString gSplit::next()
{
	if ( m_Str )
	{
        gString ret = m_next;
		m_pos1 = m_pos2 + m_tokenSize;
		m_pos2 = m_Str->find( m_Token, m_pos1 );
		m_next = m_Str->substr( m_pos1, m_pos2 - m_pos1 );

		if ( m_pos2 == gString_npos )
		{
            m_Str = nullptr;
		}
        return ret;
	}

	return "";
}

int gSplit::next_i()
{
    return gStoI(next());
}
float gSplit::next_f()
{
    return gStoF(next());
}

gSplitArray::gSplitArray( gString* InStr )
{
    m_Str = InStr;
    m_pos1 = 0;
    m_pos2 = -1;
}

gString gSplitArray::next()
{
    if ( m_Str )
    {
        m_pos1 = m_pos2 + 1;
        m_pos2 = m_Str->find( " ", m_pos1 );
        if ( m_pos2 != gString_npos )
        {
            int len = gStoI( m_Str->substr( m_pos1, m_pos2 - m_pos1 ) );
            m_pos1 = m_pos2 + 1;
            m_pos2 += len + 1;
            
            return m_Str->substr( m_pos1, m_pos2 - m_pos1 );
        }
        m_Str = nullptr;
    }
    return "";
}

GZY_NAMESPACE_END
