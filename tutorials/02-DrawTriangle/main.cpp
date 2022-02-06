#include <Windows.h>
#include <SmartFCCS/SmartFCCS.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    auto window = CreateWindowF(L"fccs", 800, 600);
    auto device = CreateDevice();
    auto swapchain = CreateSwapChain(window.get(), device.get(), DXGI_FORMAT_R8G8B8A8_UNORM);
    window->ShowWindow();

    Microsoft::WRL::ComPtr<ID3DBlob> vs_blob, ps_blob;
    D3DCompileFromFile(L"vs.hlsl", nullptr, nullptr, "main", "vs_5_0", 0, 0, &vs_blob, nullptr);
    D3DCompileFromFile(L"ps.hlsl", nullptr, nullptr, "main", "ps_5_0", 0, 0, &ps_blob, nullptr);
    auto device_ptr = reinterpret_cast<ID3D11Device*>(device->GetNativePointer());
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
    device_ptr->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs);
    Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
    device_ptr->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &ps);

    D3D11_INPUT_ELEMENT_DESC desc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    device_ptr->CreateInputLayout(desc, 1, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &layout);

    while (window->IsRun()) {
        swapchain->Present();
    }
    return 0;
}
