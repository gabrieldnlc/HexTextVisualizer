#pragma once

#include "MirroredHex.hpp"
#include "UI.hpp"

namespace gui
{
	using tables::MirroredHex;

	class Application
	{
	public:
		Application(MirroredHex&& hex);
		int Start();
	private:
		UI app;
	};
}