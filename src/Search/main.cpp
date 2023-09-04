#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "WeightedGraph.h"

using namespace MMAlg::Graph;

int main()
{
	int nodes = 0;
	StaticNode node{"1 3",2,3};
	StaticNode node1{ "2 4",4,5 };
	StaticNode node2{ "3 2",0,0 };
	StaticNode node3{ "4 4",0,0 };
	StaticNode node4{ "5 4",0,0 };

	StaticBinTree tree;
	tree.addNode(node);
	tree.addNode(node1);
	tree.addNode(node2);
	tree.addNode(node3);
	tree.addNode(node4);

	tree.BFS([&nodes](StaticNode& node) -> void
		{
			std::string data{ node.dataBuffer };
			nodes += stoi(data.substr(2, 1));
		}, [](StaticNode& node) -> int
			{
				return 1;
			});

	std::cout << nodes << '\n';
	

	WeightedGraph wg;
	Node n1, n2, n3, n4, n5;
	n1.id = 1;
	n2.id = 2;
	n3.id = 3;
	n4.id = 4;
	n5.id = 5;

	wg.addNode(n1);
	wg.addNode(n2);
	wg.addNode(n3);
	wg.addNode(n4);
	wg.addNode(n5);
	
	wg.addEdge(std::make_shared<Node>(n1), std::make_shared<Node>(n2), 2);
	wg.addEdge(std::make_shared<Node>(n2), std::make_shared<Node>(n3), 2);
	wg.addEdge(std::make_shared<Node>(n1), std::make_shared<Node>(n3), 2);
	wg.addEdge(std::make_shared<Node>(n4), std::make_shared<Node>(n5), 2);
	wg.addEdge(std::make_shared<Node>(n1), std::make_shared<Node>(n5), 2);

	std::cout << wg.isConnected();
	wg.Dijkstra(std::make_shared<Node>(n1));




	system("pause");
	return 0;
}