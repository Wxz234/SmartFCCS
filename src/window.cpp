#include "window.h"
#include <mutex>
namespace SmartFCCS {

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }
    void RegisterClassOnce() {
        static std::once_flag oc;
        std::call_once(oc,
            []() {
                WNDCLASSEXW wcex = {};
                wcex.cbSize = sizeof(WNDCLASSEXW);
                wcex.style = CS_HREDRAW | CS_VREDRAW;
                wcex.lpfnWndProc = WndProc;
                wcex.hInstance = GetModuleHandle(nullptr);
                wcex.hIcon = LoadIconW(wcex.hInstance, L"IDI_ICON");
                wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
                wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
                wcex.lpszClassName = L"fccs_class";
                wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");

                RegisterClassExW(&wcex);
            }
        );
    }


	Window::Window(const wchar_t* title, uint32_t width, uint32_t height) {
        RegisterClassOnce();
        RECT rc = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, FALSE);
        m_Hwnd = CreateWindowExW(0, L"fccs_class", title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, GetModuleHandle(nullptr), this);
        ZeroMemory(&msg, sizeof(MSG));
        w = width;
        h = height;
    }

	void Window::ShowWindow() {
        ::ShowWindow(m_Hwnd, SW_SHOWDEFAULT);
    }

    bool Window::IsRun() {
        if (WM_QUIT == msg.message) {
            return false;
        }
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }

	FCCS_API IWindow* CreateWindowF(const wchar_t* title, uint32_t width, uint32_t height) {
        static Window* ptr = new Window(title, width, height);
		return ptr;
	}
}