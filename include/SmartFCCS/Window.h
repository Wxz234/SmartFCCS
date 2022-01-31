#pragma once
#include "Core.h"
#include <cstdint>
namespace SmartFCCS {
	struct Window {

	};

	Window* CreateWinodwF(const wchar_t* title, uint32_t width, uint32_t height);
}