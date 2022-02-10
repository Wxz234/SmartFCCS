#pragma once
#include "pch.h"
#include <SmartFCCS/Window.h>
namespace SmartFCCS {
	class Window : public IWindow {
	public:
		Window(const wchar_t* title, uint32_t width, uint32_t height);
		void ShowWindow();
		bool IsRun();
		void DispatchWindowMessage();
		MSG msg;
		HWND m_Hwnd;

		uint32_t w;
		uint32_t h;
	};
}