#include "WeightedGraph.h"
#include <cassert>
#include <algorithm>
#include <queue>



namespace MMAlg::Graph
{


	void WeightedGraph::addEdge(const std::shared_ptr<Node>& startNode, const std::shared_ptr<Node> endNode, int weight)
	{
#ifdef _DEBUG
		auto beg = m_nodes.cbegin();
		auto end = m_nodes.cend();
#endif
		for (const auto& edge : m_edges)
		{
			if ((*startNode == *edge->eNode && *endNode == *edge->sNode) || (*startNode == *edge->sNode && *endNode == *edge->eNode))
			{
				assert(false);
				edge->weight = weight;
				return;
			}
		}
		m_edges.emplace_back(std::make_shared<Edge>(startNode, endNode, weight));
	}
	void WeightedGraph::addEdge(const std::shared_ptr<Edge>& newEdge)
	{
#ifdef _DEBUG
		auto beg = m_nodes.cbegin();
		auto end = m_nodes.cend();
#endif
		for (const auto& edge : m_edges)
		{
			if ((*edge->sNode == *newEdge->eNode && *edge->eNode == *newEdge->sNode) || (*edge->sNode == *newEdge->sNode && *edge->eNode == *newEdge->eNode))
			{
				assert(false);
				edge->weight = newEdge->weight;
				return;
			}
		}
		m_edges.emplace_back(newEdge);
	}

	auto WeightedGraph::isConnected() const -> bool
	{
		using Set = MMAlg::Set::DSet;
		Set set(m_nodes);
		for (auto& edge : m_edges)
		{
			const auto beg = m_nodes.begin();
			const auto end = m_nodes.end();
			const std::size_t x = std::find_if(beg, end, [&edge](const std::shared_ptr<Node> now_ptr)->bool
				{
					return *now_ptr == *(edge->sNode);
				}) - beg;
			const std::size_t y = std::find_if(beg, end, [&edge](const std::shared_ptr<Node> now_ptr)->bool
				{
					return *now_ptr == *(edge->eNode);
				}) - beg;
			if (x < m_edges.size() && y < m_edges.size())
				set.add(x, y);
			else
				assert(false);
		}

		for (std::size_t i = 0; i < m_nodes.size() - 2; ++i)
		{
			if (set.find(i) != set.find(i + 1))
				return false;
		}

		return true;
	}

	void WeightedGraph::Dijkstra(const std::shared_ptr<Node>& startNode_ptr, std::vector<std::shared_ptr<Node>> preNodes)
	{
		auto beg_Iter = m_nodes.cbegin();
		auto end_Iter = m_nodes.cend();
		auto startNode_Iter = std::find_if(beg_Iter, end_Iter, 
			[&startNode_ptr](const std::shared_ptr<Node>& now_ptr) -> bool
			{
				return *startNode_ptr == *now_ptr;
			});
		if (startNode_Iter == end_Iter)
		{
			assert(false);
			return;
		}
		
		std::vector<bool> done(m_nodes.size(), false);
		preNodes.assign(m_nodes.size(), nullptr);
		m_wightSum.assign(m_nodes.size(), INF);
		m_wightSum.at(startNode_Iter - beg_Iter) = 0;
		std::priority_queue<std::shared_ptr<Node>> nodes_q;
		nodes_q.push(*startNode_Iter);

		while (!nodes_q.empty())
		{
			const std::shared_ptr<Node> u = nodes_q.top();
			const std::size_t index = std::find_if(beg_Iter, end_Iter,
				[&u](const std::shared_ptr<Node>& now_ptr) -> bool
				{
					return *u == *now_ptr;
				}) - beg_Iter;
			assert(index < m_nodes.size());
			nodes_q.pop();
			if (done.at(index)) continue;
			done.at(index) = true;

			for (const auto& neibor : this->findNeibor(u))
			{
				const std::size_t neiborIndex = std::find_if(beg_Iter, end_Iter,
					[&neibor](const std::shared_ptr<Node>& now_ptr) -> bool
					{
						return *neibor == *now_ptr;
					}) - beg_Iter;
				assert(neiborIndex < m_nodes.size());
				if (done.at(neiborIndex)) continue;
				if (m_wightSum.at(neiborIndex) > add(this->getWeight(u, neibor), m_wightSum.at(index)))
				{
					m_wightSum.at(neiborIndex) = add(this->getWeight(u, neibor), m_wightSum.at(index));
					nodes_q.push(neibor);
					preNodes.at(neiborIndex) = u;
				}
			}
		}
	}

	inline std::vector<std::shared_ptr<Node>> WeightedGraph::findNeibor(const std::shared_ptr<Node>& node) const
	{
		std::vector<std::shared_ptr<Node>> result;
		for (const auto& edge : m_edges)
		{
			if (*edge->eNode == *node)
				result.emplace_back(edge->sNode);
			else if (*edge->sNode == *node)
				result.emplace_back(edge->eNode);	
		}

		return result;
	}

}