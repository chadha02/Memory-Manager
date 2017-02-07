#include "Source.h"

using namespace Engine;


GameObject::GameObject()
{}
GameObject::GameObject(int a, int b, int c) : m_x(a), m_y(b), m_z(c)
{ }

bool GameObject:: operator==(const GameObject & rhs)
{
	if (m_x == rhs.m_x && m_y == rhs.m_y && m_z == rhs.m_z)
		return true;
	else
		return false;
}
GameObject GameObject :: operator +(const GameObject &c1)
{

	m_x = m_x + c1.m_x;
	m_y = m_y + c1.m_y;
	m_z = m_z + c1.m_z;

	return *this;
}
GameObject GameObject :: operator -(const GameObject &c1)
{

	m_x = m_x - c1.m_x;
	m_y = m_y - c1.m_y;
	m_z = m_z - c1.m_z;

	return *this;
}

GameObject MosterController::UpdatePosition(GameObject object1, int grid)
{
	object1.setx((rand() % (2*grid+1)) + (-grid));
	object1.sety((rand() % (2 * grid + 1)) + (-grid));
	object1.setz(0);
	return object1;
}

GameObject PlayerController::UpdatePosition(GameObject object1, int p)
{
	if (p == 0)
	{
		object1.setx(1); object1.sety(0); object1.setz(0);
	}
	else if (p == 1)
	{
		object1.setx(0); object1.sety(1); object1.setz(0);
	}
	return object1;
}

GameObject PlayerRandomizer::UpdatePosition(GameObject object1, int grid)
{
	object1.setx((rand() % (2 * grid + 1)) + (-grid));
	object1.sety((rand() % (2 * grid + 1)) + (-grid));
	object1.setz(0);
	return object1;
}

