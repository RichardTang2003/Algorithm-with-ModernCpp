#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "DisJointSet.h"

namespace MMAlg::Graph
{
	const long long INF = std::numeric_limits<long long>::max();

	[[nodiscard]] inline constexpr auto
		add(const long long a, const long long b) -> long long
	{
		if (a == INF || b == INF)
		{
			return INF;
		}
		else
		{
			return a + b;
		}
	}

	struct Node
	{
		char dataBuffer[64];
		int id = -1;

		bool operator==(const Node& rhs) const 
		{
			if (id == -1 || rhs.id == -1)
			{
				assert(false);
				return false;
			}
			return id == rhs.id;
		}
	};

	struct Edge
	{
		std::shared_ptr<Node> sNode, eNode;
		int weight = 1;
	};

	class WeightedGraph
	{
	private:
		std::vector<std::shared_ptr<Node>> m_nodes;
		std::vector<std::shared_ptr<Edge>> m_edges;
		std::vector<long long> m_wightSum;

	public:
		void addNode(const std::shared_ptr<Node>& node_ptr) { m_nodes.push_back(node_ptr); }
		void addNode(const Node& node) { m_nodes.emplace_back(std::make_shared<Node>(node)); }
		void addEdge(const std::shared_ptr<Node>& startNode, const std::shared_ptr<Node> endNode, int weight);
		void addEdge(const std::shared_ptr<Edge>& Edge);

		[[nodiscard]] auto 
			isConnected() const -> bool;
		[[nodiscard]] auto
			getWeight(const std::shared_ptr<Node> startNode, const std::shared_ptr<Node> endNode) const -> int
		{
			const auto Iter = std::find_if(m_edges.cbegin(), m_edges.cend(), [&startNode, &endNode](const std::shared_ptr<Edge> now_ptr)->bool
				{
					return (*now_ptr->eNode == *startNode && *now_ptr->sNode == *endNode) || (*now_ptr->sNode == *startNode && *now_ptr->eNode == *endNode);
				});

			return (*Iter)->weight;
		}


		
		void Dijkstra(const std::shared_ptr<Node>& startNode, std::vector<std::shared_ptr<Node>> preNodes = {});

	private:
		[[nodiscard]] inline std::vector<std::shared_ptr<Node>> findNeibor(const std::shared_ptr<Node>& node) const;
	};


}
