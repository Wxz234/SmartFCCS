#include <Windows.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    constexpr uint32_t width = 800, height = 800;
    auto window = CreateWindowF(L"fccs", width, height);
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

    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    device->CreateInputLayout(0, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &layout);

    float triangleVertices[3][4] = {
        { 0.00f, 0.25f, 0.00f, 1.00f },
        { 0.25f,-0.25f, 0.00f, 1.00f },
        {-0.25f,-0.25f, 0.00f, 1.00f },
    };
    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(triangleVertices);
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = triangleVertices;
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexbuffer;
    device_ptr->CreateBuffer(&vbd, &InitData, &vertexbuffer);

    uint32_t stride = sizeof(triangleVertices) / 3;
    uint32_t offset = 0;
    auto immediateContext = device->GetDeviceContext();
    immediateContext->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);
    immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    immediateContext->IASetInputLayout(layout.Get());
    immediateContext->VSSetShader(vs.Get(), nullptr, 0);
    immediateContext->PSSetShader(ps.Get(), nullptr, 0);

    auto renderTargetView = swapchain->GetRenderTargetView();
    immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    D3D11_VIEWPORT screenViewport{ 0, 0, width, height, 0.f, 1.f };
    immediateContext->RSSetViewports(1, &screenViewport);

    while (window->IsRun()) {
        immediateContext->Draw(3, 0);
        swapchain->Present();
    }
    return 0;
}
