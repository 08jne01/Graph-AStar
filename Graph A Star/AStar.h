#pragma once
#include <vector>
#include "ItemWrapper.h"
#include <functional>
class Hash
{
public:
	Hash(int size):
		m_size(size)
	{

	}
	inline int index(Vec2i pos)
	{
		int value = pos.x & pos.y;
		return (unsigned int)((pos.x * 73856093) ^ (pos.y * 83492791)) % m_size;
	}
private:
	int m_size;
	//std::hash<int> m_hash;
};

template<class T> class HashTable
{
public:
	HashTable(int size):
		m_hash(size)
	{
		m_table.resize(size);
		for (int i = 0; i < m_table.size(); i++)
		{
			m_table[i] = nullptr;
		}
	}
	void deleteHashTable()
	{
		for (int i = 0; i < m_table.size(); i++)
		{
			delete m_table[i];
		}
	}
	T*& operator()(const Vec2i pos)
	{
		return m_table[m_hash.index(pos)];
	}
	const T*& operator()(const Vec2i pos) const
	{
		return m_table[m_hash.index(pos)];
	}

	T*& operator()(const int x, const int y)
	{
		return m_table[m_hash.index(Vec2i(x, y))];
	}
	const T*& operator()(const int x, const int y) const
	{
		return m_table[m_hash.index(Vec2i(x, y))];
	}
private:
	int m_size;
	Hash m_hash;
	std::vector<T*> m_table;
};

//Get "shortest" path between two tracks
// items    (OUT) Populated with a list of tracks between the two points
// item0    (IN) First item on the path
// item1    (IN) Second item on the path
void astar(std::vector<Object*>& items, const Object* item0, const Object* item1);
//Flood out using AStar
// items    (OUT) list of items that have been explored
// item0    (IN) start point of flood
// item1    (IN) end point of flood
//Note the items are essentially a linked list so all 
static bool flood(std::vector<ItemWrapper>& items, const Item* item0, const Item* item1);
static bool updateCost(HashTable<ItemWrapper>& table, Vec2i pos, ItemWrapper* parent, Vec2i finish);