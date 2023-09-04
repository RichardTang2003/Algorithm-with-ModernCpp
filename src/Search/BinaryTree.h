#pragma once
#include <cstddef>
#include <vector>
#include <queue>
#include <memory>

namespace MMAlg::Graph
{

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

		void addNode(const StaticNode& node);
		void addNode(const std::shared_ptr<StaticNode>& node_ptr);
		template <typename T, typename F> void BFS(T func, F eval);
		template<typename T, typename F> void DFS(T func, F eval);

		[[nodiscard]] constexpr auto
			getRoot() const->std::size_t;

	private:
		template<typename T, typename F> void staticBinTreeDFSHelper(StaticNode& node, T func, F eval);

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

		void addNode(const DynamicNode& node);
		void addNode(const std::shared_ptr<DynamicNode>& node_ptr);
		void setRoot(const DynamicNode& root) { m_root_p = std::make_shared<DynamicNode>(root); }
		template <typename T, typename F> void BFS(T func, F eval);
		template<typename T, typename F> void DFS(T func, F eval);

		[[nodiscard]] auto
			getRoot() const->DynamicNode&;


	private:
		template<typename T, typename F> void dynamicBinTreeDFSHelper(DynamicNode* node, T func, F eval);



	};


	template<typename T, typename F>
	inline void StaticBinTree::BFS(T func, F eval)
	{
		std::queue<std::size_t> searchQueue;
		searchQueue.push(m_root);
		while (!searchQueue.empty())
		{
			std::size_t nowIndex = searchQueue.front();
			StaticNode& nowNode = m_nodes.at(nowIndex);
			searchQueue.pop();
			func(m_nodes.at(nowIndex));
			if (eval(nowNode) > 0)
			{
				if (nowNode.lChild != 0) searchQueue.push(nowNode.lChild);
				if (nowNode.rChild != 0) searchQueue.push(nowNode.rChild);
			}
		}
	}

	template<typename T, typename F>
	void StaticBinTree::staticBinTreeDFSHelper(StaticNode& node, T func, F eval)
	{
		int evaluation = eval(node);
		if (evaluation > 0)
		{
			func(node);
		}
		else if (evaluation == -1)
		{
			return;
		}

		if (node.lChild != 0) staticBinTreeDFSHelper(m_nodes.at(node.lChild), func, eval);
		if (node.lChild != 0) staticBinTreeDFSHelper(m_nodes.at(node.rChild), func, eval);
	}

	template<typename T, typename F>
	inline void StaticBinTree::DFS(T func, F eval)
	{
		staticBinTreeDFSHelper(m_nodes.at(m_root), func, eval);
	}

	template<typename T, typename F>
	inline void DynamicBinTree::BFS(T func, F eval)
	{
		std::queue<std::shared_ptr<DynamicNode>> searchQueue;
		searchQueue.push(m_root_p);
		while (!searchQueue.empty())
		{
			auto& now_p = searchQueue.front();
			searchQueue.pop();
			func(*now_p);
			if (eval(*now_p) > 0)
			{
				if (now_p->lChild_p != nullptr) searchQueue.push(now_p->lChild_p);
				if (now_p->rChild_p != nullptr) searchQueue.push(now_p->rChild_p);
			}
		}
	}


	template<typename T, typename F>
	void DynamicBinTree::dynamicBinTreeDFSHelper(DynamicNode* node, T func, F eval)
	{
		int evaluation = eval(node);
		if (evaluation > 0)
		{
			func(node);
		}
		else if (evaluation == -1)
		{
			return;
		}
		if (node->lChild_p != nullptr) dynamicBinTreeDFSHelper(node.lChild_p, func, eval);
		if (node->lChild_p != nullptr) dynamicBinTreeDFSHelper(node.rChild_p, func, eval);
	}

	template<typename T, typename F>
	inline void DynamicBinTree::DFS(T func, F eval)
	{
		DynamicBinTreeDFSHelper(m_root_p, func, eval);
	}

}