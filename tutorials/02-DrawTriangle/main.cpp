#include <SmartFCCS/SmartFCCS.h>
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3dx12.h>
#include <memory>

using namespace SmartFCCS;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    constexpr unsigned width = 800, height = 800;
    constexpr DXGI_FORMAT renderformat = DXGI_FORMAT_R8G8B8A8_UNORM;
    std::unique_ptr <IWindow, fccs_deleter<IWindow>> window(CreateWindowF(L"fccs", width, height));
    window->ShowWindow();
    std::unique_ptr<IDevice, fccs_deleter<IDevice>> device(CreateDevice());
    std::unique_ptr<ICommandQueue, fccs_deleter<ICommandQueue>> queue(device->CreateCommandQueue(COMMAND_LIST_TYPE::GRAPHICS));
    std::unique_ptr<ICommandList, fccs_deleter<ICommandList>> list(device->CreateCommandList(COMMAND_LIST_TYPE::GRAPHICS));
    std::unique_ptr<ISwapChain, fccs_deleter<ISwapChain>> swapchain(CreateSwapChain(window.get(), queue.get(), renderformat));

    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootsignature;
    {
        CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        device->CreateRootSignature(&rootSignatureDesc, &rootsignature);
    }

    Microsoft::WRL::ComPtr<ID3DBlob> vertexShader;
    Microsoft::WRL::ComPtr<ID3DBlob> pixelShader;
    CompileShaderFromFile(L"vs.hlsl", nullptr, "main", SHADER_MODEL::SM_5_1, SHADER_TYPE::VERTEX, &vertexShader);
    CompileShaderFromFile(L"ps.hlsl", nullptr, "main", SHADER_MODEL::SM_5_1, SHADER_TYPE::PIXEL, &pixelShader);

    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    GRAPHICS_PIPELINE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputElementDescs, 1 };
    psoDesc.pRootSignature = rootsignature.Get();
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = renderformat;
    psoDesc.Viewport = CD3DX12_VIEWPORT(0.f, 0.f, width, height);
    psoDesc.Scissor = CD3DX12_RECT(0, 0, width, height);
    std::unique_ptr<IPipelineState, fccs_deleter<IPipelineState>> pipelineState(device->CreateGraphicsPipelineState(&psoDesc));
    vertexShader.Reset();
    pixelShader.Reset();
    float triangleVertices[3][4] = {
        { 0.00f, 0.25f, 0.00f, 1.00f },
        { 0.25f,-0.25f, 0.00f, 1.00f },
        {-0.25f,-0.25f, 0.00f, 1.00f },
    };
    std::unique_ptr<IBuffer, fccs_deleter<IBuffer>> vertexBuffer(device->CreateBuffer(sizeof(triangleVertices), HEAP_TYPE::UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ));
    vertexBuffer->Write(triangleVertices, sizeof(triangleVertices));
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
    vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = sizeof(float) * 4;
    vertexBufferView.SizeInBytes = sizeof(triangleVertices);
    
    while (window->IsRun()) {
        auto frameIndex = swapchain->GetFrameIndex();
        list->Open();
        list->SetGraphicsPipelineState(pipelineState.get());
        auto m_commandList = (ID3D12GraphicsCommandList*)list->GetNativePtr();
        list->ResourceBarrier(swapchain->GetTexture(frameIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

        auto rtvHandle = swapchain->GetRenderTargetView(frameIndex);
        m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

        const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
        m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
        m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        m_commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
        m_commandList->DrawInstanced(3, 1, 0, 0);

        list->ResourceBarrier(swapchain->GetTexture(frameIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        list->Close();
        queue->Execute(list.get());
        swapchain->Present();
    }
    //gpu completed
    queue.reset();
    return 0;
}
