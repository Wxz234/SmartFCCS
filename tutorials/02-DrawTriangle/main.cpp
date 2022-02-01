#include <Windows.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <d3dx12.h>
#include <SmartFCCS/SmartFCCS.h>
using namespace SmartFCCS;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    const DXGI_FORMAT renderformat = DXGI_FORMAT_R8G8B8A8_UNORM;
    auto window = CreateWindowF(L"fccs", 800, 600);
    auto device = CreateDevice();
    auto g_queue = device->CreateCommandQueue(COMMAND_LIST_TYPE::GRAPHICS);
    auto g_list = device->CreateCommandList(COMMAND_LIST_TYPE::GRAPHICS);
    auto swapchain = CreateSwapChain(window, g_queue, renderformat);
    window->ShowWindow();

    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
    {
        
        CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        device->CreateRootSignature(&rootSignatureDesc, &rootsignature);
    }

    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
    {
        Microsoft::WRL::ComPtr<ID3DBlob> vertexShader;
        Microsoft::WRL::ComPtr<ID3DBlob> pixelShader;

        CompileShaderFromFile(L"vs.hlsl", "main", SHADERMODEL::SM_5_1, SHADERTYPE::VERTEX, &vertexShader);
        CompileShaderFromFile(L"ps.hlsl", "main", SHADERMODEL::SM_5_1, SHADERTYPE::PIXEL, &pixelShader);

        D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = { inputElementDescs, 1 };
        psoDesc.pRootSignature = rootsignature.Get();
        psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
        psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
        psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = 0xffffffff;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = renderformat;
        psoDesc.SampleDesc.Count = 1;
        auto deviceptr = (ID3D12Device*)device->GetNativePtr();
        deviceptr->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));
    }

    {
        float triangleVertices[3][4] = {
            { 0.00f, 0.25f, 0.00f, 1.00f },
            { 0.25f,-0.25f, 0.00f, 1.00f },
            {-0.25f,-0.25f, 0.00f, 1.00f },
        };
    }

    while (window->IsRun()) {
        auto frameIndex = swapchain->GetFrameIndex();
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
