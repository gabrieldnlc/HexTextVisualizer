#pragma once

#include <vector>
#include <exception>

namespace tables
{
	using std::vector;
	using std::size_t;

	template <class T>
	class DataTraverser
	{
	public:
		DataTraverser(T divider, size_t divider_limit) : settings(divider, divider_limit)
		{

		}
		
		size_t FindData(const vector<T>& vector, size_t pos)
		{
			if (pos >= vector.size()) return -1;
			if (vector[pos] != settings.divider) return pos;
			return FindData(vector, pos + 1);
		}

		size_t FindFirstData(const vector<T>& vector)
		{
			return FindData(vector, 0);
		}

		size_t FindEndOfData(const vector<T>& vector, size_t pos)
		{
			const size_t next = pos + 1;
			if (next >= vector.size()) return pos;
			if (IsHeadOfDividerBlock(vector, next)) return pos;
			return FindEndOfData(vector, next);
		}

		bool IsHeadOfDividerBlock(const vector<T>& vector, size_t pos)
		{
			const size_t limit = pos + (settings.divider_limit - 1);
			if (limit >= vector.size()) return false;
			if (vector[pos] != settings.divider) return false;
			for (size_t i = pos; i <= limit; i++)
			{
				if (vector[i] != settings.divider) return false;
			}
			return true;
		}

		struct ParsingSettings
		{
			ParsingSettings(T divider, size_t divider_limit) : divider(divider), divider_limit(divider_limit) {}
			T divider;
			size_t divider_limit;
		}settings;

	private:
		
	};
}