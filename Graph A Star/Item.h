#pragma once
#include <Maths/Vec2.h>
#include <vector>
class Object

{
public:
	Object():
		m_pos(0)
	{

	}
	Object(const Vec2i pos) :
		m_pos(pos)
	{

	}
	Object(const int x, const int y) :
		m_pos(Vec2i(x,y))
	{

	}
	inline void addContact(Object* contact)
	{
		if (contact != this)
			m_contacts.push_back(contact);
	}
	inline Vec2i getPos() const
	{
		return m_pos;
	}
	inline const std::vector<Object*>& contacts() const
	{
		return m_contacts;
	}
private:
	Vec2i m_pos;
	std::vector<Object*> m_contacts;
};