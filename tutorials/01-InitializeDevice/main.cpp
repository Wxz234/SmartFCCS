#include <SmartFCCS/SmartFCCS.h>
#include <memory>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    std::unique_ptr <IWindow, fccs_deleter<IWindow>> window(CreateWindowF(L"fccs", 800, 600));
    window->ShowWindow();
    std::unique_ptr<IDevice, fccs_deleter<IDevice>> device(CreateDevice());
    std::unique_ptr<ICommandQueue, fccs_deleter<ICommandQueue>> queue(device->CreateCommandQueue(COMMAND_LIST_TYPE::GRAPHICS));
    std::unique_ptr<ICommandList, fccs_deleter<ICommandList>> list(device->CreateCommandList(COMMAND_LIST_TYPE::GRAPHICS));
    std::unique_ptr<ISwapChain, fccs_deleter<ISwapChain>> swapchain(CreateSwapChain(window.get(), queue.get(), DXGI_FORMAT_R8G8B8A8_UNORM));
    while (window->IsRun()) {
        list->Open();
        list->Close();
        queue->Execute(list.get());
        swapchain->Present();
    }
    queue->WaitIdle();
    return 0;
}
