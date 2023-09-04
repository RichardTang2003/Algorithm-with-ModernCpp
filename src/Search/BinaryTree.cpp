#include <cassert>
#include "BinaryTree.h"

namespace MMAlg::Graph
{


	void StaticBinTree::addNode(const StaticNode& node)
	{
		m_nodes.emplace_back(node);
	}

	void StaticBinTree::addNode(const std::shared_ptr<StaticNode>& node_ptr)
	{
		m_nodes.push_back(*node_ptr);
	}

	constexpr auto StaticBinTree::getRoot() const -> std::size_t
	{
		return m_root;
	}

	void DynamicBinTree::addNode(const DynamicNode& node)
	{
		m_nodes.emplace_back(std::make_shared<DynamicNode>(node));
	}

	void DynamicBinTree::addNode(const std::shared_ptr<DynamicNode>& node_ptr)
	{
		m_nodes.push_back(node_ptr);
	}

	auto DynamicBinTree::getRoot() const -> DynamicNode&
	{
		return *m_root_p;
	}

}