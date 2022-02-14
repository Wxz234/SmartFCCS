#include <Windows.h>
#include <wrl/client.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    uint32_t width = 800, height = 800;
    auto window = CreateWindowF(L"fccs", width, height);
    window->ShowWindow();
    auto device = CreateDevice();
    auto swapchain = CreateSwapChain(window.get(), device.get(), DXGI_FORMAT_R8G8B8A8_UNORM);

    Microsoft::WRL::ComPtr<ID3DBlob> vs_blob, ps_blob;
    D3DCompileFromFile(L"vs.hlsl", nullptr, nullptr, "main", "vs_5_0", 0, 0, &vs_blob, nullptr);
    D3DCompileFromFile(L"ps.hlsl", nullptr, nullptr, "main", "ps_5_0", 0, 0, &ps_blob, nullptr);
    auto device_ptr = reinterpret_cast<ID3D11Device*>(device->GetNativePointer());
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
    device_ptr->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs);
    Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
    device_ptr->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &ps);

    auto deviceContext = device->GetDefaultDeviceContext();
    auto immediateContext = reinterpret_cast<ID3D11DeviceContext*>(deviceContext->GetNativePointer());
    immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    immediateContext->VSSetShader(vs.Get(), nullptr, 0);
    immediateContext->PSSetShader(ps.Get(), nullptr, 0);

    auto renderTargetView = swapchain->GetRenderTargetView();
    immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    D3D11_VIEWPORT screenViewport{ 0, 0, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f };
    immediateContext->RSSetViewports(1, &screenViewport);

    Camera camera;
    camera.SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    auto camera_mat = camera.GetViewMatrix() * camera.GetProjectionMatrix();

    D3D11_BUFFER_DESC cbd = {};
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.ByteWidth = sizeof(camera_mat);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    auto constantbuffer = device->CreateBuffer(&cbd, nullptr);
    auto constantbuffer_ptr = reinterpret_cast<ID3D11Buffer*>(constantbuffer->GetNativePointer());
    immediateContext->VSSetConstantBuffers(0, 1, &constantbuffer_ptr);
    while (window->IsRun()) {
        window->DispatchWindowMessage();
        deviceContext->UpdateBuffer(constantbuffer.get(), &camera_mat, sizeof(camera_mat));
        immediateContext->Draw(3, 0);
        swapchain->Present();
    }
    return 0;
}
