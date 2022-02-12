#include <Windows.h>
#include <wrl/client.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    uint32_t width = 800, height = 600;
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

    Camera camera(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, 1), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMConvertToRadians(45.f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f);
    auto camera_mat = camera.GetVP();

    D3D11_BUFFER_DESC cbd = {};
    cbd.Usage = D3D11_USAGE_IMMUTABLE;
    cbd.ByteWidth = sizeof(camera_mat);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    D3D11_SUBRESOURCE_DATA subdata = {};
    subdata.pSysMem = &camera_mat;
    Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
    device_ptr->CreateBuffer(&cbd, &subdata, &constantBuffer);
    immediateContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
    while (window->IsRun()) {
        window->DispatchWindowMessage();
        immediateContext->Draw(3, 0);
        swapchain->Present();
    }
    return 0;
}
