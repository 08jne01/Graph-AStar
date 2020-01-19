#include "AStar.h"
#include <Maths/Maths.h>
#include <iostream>
#include <fstream>
#include <sstream>

static void createObjects(std::vector<Object>& objects, const std::vector<std::vector<bool>>& graph, const std::vector<Vec2i>& positions);
static bool readGraphFromFile(const std::string& filename, std::vector<std::vector<bool>>& graph, std::vector<Vec2i>& positions);

int main()

{
	srand(20);
	std::vector<Object> objects;
	/*for (int i = 0; i < 20; i++)
	{
		objects.push_back(Object(Vec2i(randomi(0, 1000), randomi(0, 1000))));
	}
	
	for (int i = 0; i < objects.size(); i++)
	{
		int numContacts = randomi(1, 10);
		for (int j = 0; j < numContacts; j++)
		{
			objects[i].addContact(&objects[randomi(0, 19)]);
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		std::cout << "Index: " << i << " Pos: " << objects[i].getPos() << " Num Contacts: " << objects[i].contacts().size() << std::endl;
	}*/

	/*objects.push_back(Object(5, 0));
	objects.push_back(Object(0, 100));
	objects.push_back(Object(10, 10));
	objects.push_back(Object(20, 20));

	objects[0].addContact(&objects[1]);
	objects[0].addContact(&objects[2]);

	objects[1].addContact(&objects[0]);
	objects[1].addContact(&objects[3]);

	objects[2].addContact(&objects[0]);
	objects[2].addContact(&objects[3]);

	objects[3].addContact(&objects[1]);
	objects[3].addContact(&objects[2]);*/

	std::vector<Object*> items;
	
	std::vector<std::vector<bool>> graph;
	std::vector<Vec2i> positions;
	readGraphFromFile("network.txt", graph, positions);
	createObjects(objects, graph, positions);

	astar(items, &objects[1], &objects[3]);
	system("PAUSE");
	return 0;
}

static void createObjects(std::vector<Object>& objects, const std::vector<std::vector<bool>>& graph, const std::vector<Vec2i>& positions)
{
	for (int i = 0; i < positions.size(); i++)
	{
		objects.push_back(Object(positions[i]));
	}

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			if (graph[i][j])
				objects[i].addContact(&objects[j]);
		}
	}
}

static bool readGraphFromFile(const std::string& filename, std::vector<std::vector<bool>>& graph, std::vector<Vec2i>& positions)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		bool loadGraph = true;
		int columns = -1;
		int prevColumns = -1;
		std::vector<std::vector<int>> data;
		while (file.good())
		{
			std::string line;
			getline(file, line, '\n');
			std::stringstream streamLine;
			streamLine << line;
			std::vector<int> lineBuffer;
			for (int i = 0;; i++)
			{
				columns = i;
				getline(streamLine, line, ',');
				if (streamLine.fail())
					break;
				int value;
				std::stringstream os(line);
				os >> value;
				lineBuffer.push_back(value);
				//std::cout << value << std::endl;
			}
			data.push_back(lineBuffer);
			if (prevColumns != -1 && prevColumns != columns && columns != 2)
			{
				std::cout << "Error in file formatting" << std::endl;
				return false;
			}
			prevColumns = columns;
		}

		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].size() == 2)
			{
				positions.push_back(Vec2i(data[i][0], data[i][1]));
			}
			else
			{
				std::vector<bool> vertexConns;
				for (int j = 0; j < data[i].size(); j++)
				{
					vertexConns.push_back(data[i][j]);
				}
				graph.push_back(vertexConns);
			}
		}
		if (positions.size() != graph.size())
		{
			std::cout << "Error in file formating" << std::endl;
			return false;
		}

		for (int i = 0; i < graph.size(); i++)
		{
			if (graph.size() != graph[i].size())
			{
				std::cout << "Error in file formating" << std::endl;
				return false;
			}
		}
	}
	else
	{
		std::cout << "Error opening file" << std::endl;
		return false;
	}
	return true;
}