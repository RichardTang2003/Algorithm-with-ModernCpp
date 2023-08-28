#include <iostream>
#include <string>
#include "BFS&DFS.h"

int main()
{
	int nodes = 0;
	StaticNode node{"1 3",2,3};
	StaticNode node1{ "2 4",4,5 };
	StaticNode node2{ "3 2",0,0 };
	StaticNode node3{ "4 4",0,0 };
	StaticNode node4{ "5 4",0,0 };

	StaticBinTree tree;
	tree.insert(node);
	tree.insert(node1);
	tree.insert(node2);
	tree.insert(node3);
	tree.insert(node4);

	tree.DFS([&nodes](StaticNode& node) -> void
		{
			std::string data{ node.dataBuffer };
			nodes += stoi(data.substr(2, 1));
		},  [](StaticNode& node)
			{
				return true;
			});

	std::cout << nodes;
	system("pause");
}