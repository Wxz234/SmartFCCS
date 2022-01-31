#pragma once
#include <SmartFCCS/Window.h>
#include <Windows.h>
namespace SmartFCCS {
	class Window : public IWindow {
	public:
		Window(const wchar_t* title, uint32_t width, uint32_t height);
		void ShowWindow();
		bool IsRun();
		MSG msg;
		HWND m_Hwnd;

		uint32_t w;
		uint32_t h;
	};
}