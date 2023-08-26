#pragma once
#include <cstddef>
#include <vector>
#include <queue>
#include <memory>

struct StaticNode
{
	char dataBuffer[32];
	std::size_t lChild = 0;
	std::size_t rChild = 0;
};

class StaticBinTree
{
private:


	std::vector<StaticNode> m_nodes{ StaticNode{} };
	const std::size_t m_root = 1;

public:
	StaticBinTree() = default;
	StaticBinTree(StaticBinTree& ori) = delete;
	StaticBinTree(StaticBinTree&& ori) = default;
	~StaticBinTree() = default;
	
	StaticBinTree& operator=(StaticBinTree& rhs) = delete;
	StaticBinTree& operator=(StaticBinTree&& rhs) = default;

	StaticBinTree(std::size_t rootIndex) : m_root(rootIndex) {}

	void insert(const StaticNode& node);
	template <typename T> void BFS(T func);
	template <typename T> void DFS(T func);
	
	[[nodiscard]] constexpr auto
		getRoot() const->std::size_t;


};

struct DynamicNode
{
	char dataBuffer[32];
	std::shared_ptr<DynamicNode> lChild_p = nullptr;
	std::shared_ptr<DynamicNode> rChild_p = nullptr;
};

class DynamicBinTree
{
private:
	std::vector<std::shared_ptr<DynamicNode>> m_nodes;
	std::shared_ptr<DynamicNode> m_root_p;

public:
	DynamicBinTree() = default;
	DynamicBinTree(DynamicBinTree& ori) = delete;
	DynamicBinTree(DynamicBinTree&& ori) = default;
	~DynamicBinTree() = default;

	DynamicBinTree& operator=(DynamicBinTree& rhs) = delete;
	DynamicBinTree& operator=(DynamicBinTree&& rhs) = default;

	DynamicBinTree(const DynamicNode& root) : m_root_p(std::make_shared<DynamicNode>(root)) {}

	void insert(const DynamicNode& node);
	void setRoot(const DynamicNode& root) { m_root_p = std::make_shared<DynamicNode>(root); }
	template <typename T> void BFS(T func);
	template <typename T> void DFS(T func);


	[[nodiscard]] auto
		getRoot() const->DynamicNode&;

};


template<typename T>
inline void StaticBinTree::BFS(T func)
{
	std::queue<std::size_t> searchQueue;
	searchQueue.push(m_root);
	while (!searchQueue.empty())
	{
		std::size_t nowIndex = searchQueue.front();
		StaticNode& nowNode = m_nodes.at(nowIndex);
		searchQueue.pop();
		func(m_nodes.at(nowIndex));
		if (nowNode.lChild != 0) searchQueue.push(nowNode.lChild);
		if (nowNode.rChild != 0) searchQueue.push(nowNode.rChild);
	}
}

template<typename T>
inline void DynamicBinTree::BFS(T func)
{
	std::queue<std::shared_ptr<DynamicNode>> searchQueue;
	searchQueue.push(m_root_p);
	while (!searchQueue.empty())
	{
		auto& now_p =  searchQueue.front();
		searchQueue.pop();
		func(*now_p);
		if (now_p->lChild_p != nullptr) searchQueue.push(now_p->lChild_p);
		if (now_p->rChild_p != nullptr) searchQueue.push(now_p->rChild_p);

	}
}
