#pragma once
#include <cctype>
#include <vector>
#include <numeric>

namespace MMAlg::Set
{
	class DSet
	{
	private:
		std::vector<std::size_t> m_sets;

	public:
		template <typename T>
		DSet(const std::vector<T>& data) :
			m_sets(data.size())
		{
			std::iota(m_sets.begin(), m_sets.end(), 0);
		}



		[[nodiscard]] std::size_t find(const std::size_t id)
		{
			std::size_t& parent = m_sets.at(id);
			if (id != parent)
			{
				parent = find(parent);
			}
			return parent;
		}

		void add(std::size_t x, std::size_t y)
		{
			x = find(x);
			y = find(y);
			if (x != y)
				m_sets.at(x) = m_sets.at(y);
		}
	};
}
