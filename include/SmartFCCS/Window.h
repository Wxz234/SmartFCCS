#pragma once
#include "Core.h"
#include <cstdint>
namespace SmartFCCS {
	struct IWindow : public IObject {
		virtual void ShowWindow() = 0;
		virtual bool IsRun() = 0;
	};
	using WindowUniquePtr = std::unique_ptr<IWindow, void(*)(IWindow*)>;
	FCCS_API WindowUniquePtr CreateWindowF(const wchar_t* title, uint32_t width, uint32_t height);
}