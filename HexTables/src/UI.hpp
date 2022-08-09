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
	private:
		vector<int> hex;
		string name;
	};
}