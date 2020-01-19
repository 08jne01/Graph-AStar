#pragma once
#include "Item.h"
#include "Heap.h"
class ItemWrapper : public Item
{
public:
	ItemWrapper(const Object* item):
		m_item(item)
	{

	}
	inline Vec2i getItemPos()
	{
		return m_item->getPos();
	}
	int compareTo(ItemWrapper& other)
	{
		int compare = 0;
		if (m_fCost < other.fCost())
			compare = 1;
		else if (m_fCost > other.fCost())
			compare = -1;

		if (!compare)
		{
			if (m_hCost < other.hCost())
				compare = 1;
			else if (m_hCost > other.hCost())
				compare = -1;
		}
		return compare;
	}
	inline int fCost() const
	{
		return m_fCost;
	}
	inline int gCost() const
	{
		return m_gCost;
	}
	inline int hCost() const
	{
		return m_hCost;
	}
	inline void fCost(int f)
	{
		m_fCost = f;
	}
	inline void gCost(int g)
	{
		m_gCost = g;
	}
	inline void hCost(int h)
	{
		m_hCost = h;
	}
	inline const std::vector<Object*>& contacts() const
	{
		return m_item->contacts();
	}
	ItemWrapper* parent()
	{
		return m_parent;
	}
	void parent(ItemWrapper* parent)
	{
		m_parent = parent == this ? nullptr : parent;
	}
private:
	const Object* m_item;

	int m_gCost = 100000; //actual cost of the path from the start to the current point
	int m_hCost = 0; //heuristic cost -> euclidian distance in this case
	int m_fCost = 100000; //gCost + hCost
	ItemWrapper* m_parent = nullptr;
};