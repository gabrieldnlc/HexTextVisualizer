#pragma once

#include <vector>
#include <string>

namespace gui
{
	using std::vector;
	using std::string;

	class UI
	{
	public:
		UI(vector<int>&& hex, string name);
		void Render();

		vector<int> hex;
		string name;

		int divider = 0;
		int divider_limit = 3;

		int first_byte;
		int last_byte;
	};
}