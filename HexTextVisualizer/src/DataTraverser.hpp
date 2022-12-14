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
			if (pos >= vector.size()) return std::string::npos;
			if (vector[pos] != settings.divider) return pos;
			return FindData(vector, pos + 1);
		}

		size_t FindFirstData(const vector<T>& vector)
		{
			return FindData(vector, 0);
		}
		
		size_t FindEndOfData(const vector<T>& vector, int pos, int limit = -1)
		{
			size_t next = pos + 1;
			if (next >= vector.size() || (limit >= 0 && pos >= limit)) return pos;
			while (next < vector.size())
			{
				if (IsHeadOfDividerBlock(vector, next)) return next - 1;
				next++;
			}
			return next - 1;
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
			ParsingSettings(T divider, int divider_limit) : divider(divider), divider_limit(divider_limit) {}
			T divider;
			int divider_limit;
		}settings;

	private:
		
	};
}