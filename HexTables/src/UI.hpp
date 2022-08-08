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
		UI(vector<uint8_t>&& hex, string name);
		void Render();
	private:
		vector<uint8_t> hex;
		string name;
	};
}