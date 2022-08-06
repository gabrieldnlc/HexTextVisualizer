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
		size_t WhereIsEndOfData(const vector<T>& v, size_t pos)
		{
			if (pos + 1 >= v.size()) return pos;
			if (IsDividerBlock(v, pos + 1)) return pos;
			return (WhereIsEndOfData(v, pos + 1));

		}
		size_t WhereIsNextData(const vector<T>& v, size_t pos)
		{
			if (pos >= v.size()) return -1;
			if (pos + 1 >= v.size()) return -1;
			if (v[pos] != settings.divider) return pos;
			if (IsDividerBlock(v, pos)) return pos + settings.divider_limit - 1;
			return WhereIsNextData(v, pos + 1);			
		}

		struct ParsingSettings
		{
			ParsingSettings(T divider, size_t divider_limit) : divider(divider), divider_limit(divider_limit) {}
			T divider;
			size_t divider_limit;
		}settings;

	private:
		bool IsDividerBlock(const vector<T>& v, size_t pos)
		{
			if (pos + settings.divider_limit - 1 >= v.size()) return false;
			size_t count = 0;
			try
			{
				for (size_t i = 0; i < settings.divider_limit; i++)
				{
					if (v[pos + i] == settings.divider)
					{
						count++;
						if (count == settings.divider_limit)
						{
							return true;
						}
					}
					else
					{
						return false;
					}
				}
				return false;
			}
			catch (const std::exception&)
			{
				return true;
			}
		}
	};
}