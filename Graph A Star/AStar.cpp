#include "AStar.h"
#include "Heap.h"
#include <Maths/Maths.h>
#include <functional>

static void backTrack(ItemWrapper* last);



//Get "shortest" path between two tracks
// items    (OUT) Populated with a list of tracks between the two points
// item0    (IN) First item on the path
// item1    (IN) Second item on the path
void astar(std::vector<Object*>& items, const Object* item0, const Object* item1)
{
	std::vector<ItemWrapper*> itemsWrapped;
	Heap<ItemWrapper> open(1000);
	HashTable<ItemWrapper> table(1000);

	ItemWrapper* current = new ItemWrapper(item0);
	table(item0->getPos()) = current;
	updateCost(table, item0->getPos(), nullptr, item1->getPos());
	open.add(current);
	bool first = true;

	//itemsWrapped.push_back(current);

	std::cout << "Start Position " << item0->getPos() << std::endl;

	while (current)
	{
		current = open.removeFirst();

		if (!current)
			break;

		if (current->getItemPos() == item1->getPos())
		{
			std::cout << "Final Position " << item1->getPos() << " Done!" << std::endl;
			backTrack(current);
			break;
		}
		for (int i = 0; i < current->contacts().size(); i++)
		{
			Vec2i nextPos = current->contacts()[i]->getPos();
			if (!table(nextPos))
			{
				table(nextPos) = new ItemWrapper(current->contacts()[i]);
			}
			bool better = updateCost(table, nextPos, current, item1->getPos());
			ItemWrapper* nextItem = table(nextPos);
			if (!open.contains(nextItem))
			{
				if (better && nextItem != current)
				{
					open.add(nextItem);
				}
			}
			else
			{
				open.updateItem(nextItem);
			}
		}	
	}

	table.deleteHashTable();
}

static bool updateCost(HashTable<ItemWrapper>& table, Vec2i pos, ItemWrapper* parent, Vec2i finish)
{
	int gCostNew;
	int hCostNew;
	int fCostNew;

	hCostNew = std::floor(distance(finish, pos));

	if (parent)
	{
		Vec2i posParent = parent->getItemPos();
		int dist = distance(posParent, pos);
		gCostNew = parent->gCost() + dist;
	}
	else
	{
		table(pos)->fCost(hCostNew);
		table(pos)->gCost(0);
		table(pos)->hCost(hCostNew);
		return true;
	}

	if (gCostNew < table(pos)->gCost())
	{
		fCostNew = gCostNew + hCostNew;
		table(pos)->fCost(fCostNew);
		table(pos)->gCost(gCostNew);
		table(pos)->hCost(hCostNew);
		table(pos)->parent(parent);
		return true;
	}
	return false;
}

//Go from last item to first item and add ItemWrappers to a list of items
// items    (OUT) Populated with a list of tracks from backtrack
// finalItem (IN) The item to start the backtrack on
void backTrack(ItemWrapper* last)
{
	for (ItemWrapper* i = last; i != nullptr; i = i->parent())
	{
		std::cout << i->getItemPos() << std::endl;
	}
}

//Flood out using AStar
// items    (OUT) list of items that have been explored
// item0    (IN) start point of flood
// item1    (IN) end point of flood
//Note the items are essentially a linked list so all 
static bool flood(std::vector<ItemWrapper>& items, const Item* item0, const Item* item1)
{

}