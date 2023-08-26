#include <cassert>
#include "BFS&DFS.h"


void StaticBinTree::insert(const StaticNode& node)
{
	m_nodes.emplace_back(node);
}

constexpr auto StaticBinTree::getRoot() const -> std::size_t
{
	return m_root;
}

void DynamicBinTree::insert(const DynamicNode& node)
{
	m_nodes.emplace_back(std::make_shared<DynamicNode>(node));
}

auto DynamicBinTree::getRoot() const -> DynamicNode&
{
	return *m_root_p;
}
