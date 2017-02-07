#ifndef ASSERT_H
#define ASSERT_H

#define DEBUGGER_BREAK __debugbreak()

namespace Engine
{
	bool _MessagedAssert(const char * i_pExp, const char * i_pMessage, const char * i_pFile, unsigned int i_LineNo);
}

#ifdef NDEBUG

#define MessagedAssert(_Expression,_Message)     ((void)0)

#else

#define MessagedAssert(_Expression,_Message) if( (!(_Expression)) && !Engine::_MessagedAssert(#_Expression, _Message, __FILE__, __LINE__) ) { DEBUGGER_BREAK; }

#endif  

#endif 