#include <Windows.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    auto window = CreateWindowF(L"fccs", 800, 600);
    auto device = CreateDevice();
    auto g_queue = device->CreateCommandQueue(COMMAND_LIST_TYPE::GRAPHICS);
    auto g_list = device->CreateCommandList(COMMAND_LIST_TYPE::GRAPHICS);
    auto swapchain = CreateSwapChain(window, g_queue);
    window->ShowWindow();
    while (window->IsRun()) {
        g_list->Open();
        g_list->Close();
        g_queue->Execute(g_list);
        swapchain->Present();
    }
    DestroyObject(swapchain);
    DestroyObject(g_list);
    DestroyObject(g_queue);
    DestroyObject(device);
    DestroyObject(window);
    return 0;
}
