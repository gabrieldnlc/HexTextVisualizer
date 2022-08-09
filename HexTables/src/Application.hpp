#pragma once

#include <vector>
#include <string>

#include "UI.hpp"

namespace gui
{
	using std::vector;
	using std::string;

	class Application
	{
	public:
		Application(vector<int>&& hex, string name);
		int Start();
	private:
		UI app;
	};
}