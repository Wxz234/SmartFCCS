#include <Windows.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    auto window = CreateWindowF(L"fccs", 800, 600);
    window->ShowWindow();
    auto device = CreateDevice();
    auto swapchain = CreateSwapChain(window.get(), device.get(), DXGI_FORMAT_R8G8B8A8_UNORM);
    //Create Deffered Contexts
    auto copycontext = device->CreateDeviceContext();
    auto rendercontext = device->CreateDeviceContext();

    while (window->IsRun()) {
        window->DispatchWindowMessage();
        swapchain->Present();
    }
    return 0;
}
