#ifndef SOURCE_INL_H
# define SOURCE_INL_H

#include <assert.h>
namespace Engine
{
	inline int GameObject::getx(void) const
	{
		return m_x;
	}

	inline int GameObject::gety(void) const
	{
		return m_y;
	}
	
	inline int GameObject::getz(void) const
	{
		return m_z;
	}

	inline void GameObject::setx(const int i_x)
	{
		m_x = i_x;
	}
	inline void GameObject::sety(const int i_y)
	{
		m_y = i_y;
	}
	inline void GameObject::setz(const int i_z)
	{
		m_z = i_z;
	}

}
#endif