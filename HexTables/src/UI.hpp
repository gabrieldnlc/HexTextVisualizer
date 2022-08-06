#pragma once

#include "MirroredHex.hpp"

namespace gui
{
	using tables::MirroredHex;

	class UI
	{
	public:
		UI(MirroredHex&& hex);
		void Render();
	private:
		MirroredHex hex;
	};
}