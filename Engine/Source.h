#ifndef SOURCE_H
# define SOURCE_H

#include <iostream>
using namespace std;
namespace Engine
{
	class GameObject
	{

		int m_x, m_y, m_z;

	public:
		GameObject();
		GameObject(int,int,int);
		inline int getx(void) const;
		inline int gety(void) const;

		inline int getz(void) const;

		inline void setx(const int i_x);
		inline void sety(const int i_y);
		inline void setz(const int i_z);
		bool operator == (const GameObject & rhs);
		GameObject operator +(const GameObject &c1);
		GameObject operator -(const GameObject &c1);
	};
		
	class GameObjectController
	{
	public:
		virtual GameObject UpdatePosition(GameObject object1, int) = 0;
	};
	
	class MosterController : public GameObjectController
	{
	public:
		 GameObject UpdatePosition(GameObject object1, int);
	};

	class PlayerController : public GameObjectController
	{
	public:
		GameObject UpdatePosition(GameObject object1, int);
	};

	class PlayerRandomizer : public GameObjectController
	{
	public:
		GameObject UpdatePosition(GameObject object1, int);
	};
}

#include "Source-inl.h"
#endif


