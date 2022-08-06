#pragma once

#include <vector>
#include <string>

#include "BinaryOpen.hpp"

namespace tables
{
	using std::vector;
	using std::uint8_t;
	using std::string;

	class MirroredHex
	{
	public:
		using iterator = vector<uint8_t>::iterator;
		using const_iterator = vector<uint8_t>::const_iterator;

		iterator begin() { return int_table.begin(); }
		iterator end() { return int_table.end(); }


		MirroredHex(vector<uint8_t>&& ints) : int_table(std::move(ints))
		{
			hex_table.reserve(int_table.size());
			for (auto i : int_table)
			{
				hex_table.emplace_back(IntAsHexString(i));
			}
		}
		vector<uint8_t> int_table;
		vector<string> hex_table;

	};
}