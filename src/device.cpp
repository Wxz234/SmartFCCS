#include "device.h"
#include "cmd.h"
#include "gpuresource.h"
#include "pipeline.h"
#include "dx12_backend.h"
#include "DDSTextureLoader12.h"
namespace SmartFCCS {
	Device::Device() {
#if defined(_DEBUG)
		Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
#endif
		CheckDXError(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device)));
		m_queue = CreateCommandQueue(COMMAND_LIST_TYPE::COPY);
		m_list = CreateCommandList(COMMAND_LIST_TYPE::COPY);
	}

	ITexture* Device::CreateDDSTextureFromFile(const wchar_t* filename, D3D12_RESOURCE_STATES state) {
		std::unique_ptr<uint8_t[]> ddsData;
		std::vector<D3D12_SUBRESOURCE_DATA> subresources;
		Microsoft::WRL::ComPtr<ID3D12Resource> tex;
		DirectX::LoadDDSTextureFromFile(m_Device.Get(), filename, tex.ReleaseAndGetAddressOf(), ddsData, subresources);
		const UINT64 uploadBufferSize = GetRequiredIntermediateSize(tex.Get(), 0, static_cast<UINT>(subresources.size()));
		CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);	
		auto desc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
		Microsoft::WRL::ComPtr<ID3D12Resource> uploadRes;
		m_Device->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(uploadRes.GetAddressOf()));
		m_list->Open();
		auto list_ptr = (ID3D12GraphicsCommandList*)m_list->GetNativePtr();
		UpdateSubresources(list_ptr, tex.Get(), uploadRes.Get(),
			0, 0, static_cast<UINT>(subresources.size()), subresources.data());

		if (state != D3D12_RESOURCE_STATE_COPY_DEST) {
			auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(tex.Get(),
				D3D12_RESOURCE_STATE_COPY_DEST, state);
			list_ptr->ResourceBarrier(1, &barrier);
		}
		m_list->Close();
		m_queue->Execute(m_list);
		m_queue->WaitIdle();
		return new Texture(tex.Get(), tex->GetDesc().Format);
	}

	ITexture* Device::CreateTexture(uint32_t width, uint32_t height, uint32_t levels, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* pOptimizedClearValue, D3D12_RESOURCE_STATES state) {
		Microsoft::WRL::ComPtr<ID3D12Resource> myTexture;
		CD3DX12_HEAP_PROPERTIES prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		auto texDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height, 1, levels, 1, 0, flag);
		m_Device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &texDesc, state, pOptimizedClearValue, IID_PPV_ARGS(&myTexture));
		return new Texture(myTexture.Get(), format);
	}

	void Device::WaitIdle() {
		//m_queue->WaitIdle();
	}
	Device::~Device() {
		WaitIdle();
		DestroyObject(m_queue);
		DestroyObject(m_list);
	}
	IPipelineState* Device::CreateGraphicsPipelineState(const GRAPHICS_PIPELINE_DESC* pDesc) {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = pDesc->InputLayout;
		psoDesc.pRootSignature = pDesc->pRootSignature;
		psoDesc.VS = pDesc->VS;
		psoDesc.PS = pDesc->PS;
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		psoDesc.SampleMask = 0xffffffff;
		psoDesc.PrimitiveTopologyType = pDesc->PrimitiveTopologyType;
		psoDesc.NumRenderTargets = pDesc->NumRenderTargets;
		for (uint32_t i = 0;i < 8; ++i) {
			psoDesc.RTVFormats[i] = pDesc->RTVFormats[i];
		}
		psoDesc.DSVFormat = pDesc->DSVFormat;
		psoDesc.SampleDesc.Count = 1;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pso;
		CheckDXError(m_Device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso)));
		return new GraphicsPipelineState(pso.Get(), psoDesc.pRootSignature, pDesc->Viewport, pDesc->Scissor);
	}

	HRESULT Device::CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, ID3D12RootSignature** ppvRootSignature) {
		Microsoft::WRL::ComPtr<ID3DBlob> signature;
		Microsoft::WRL::ComPtr<ID3DBlob> error;
		CheckDXError(D3D12SerializeRootSignature(pRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		return m_Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(ppvRootSignature));
	}

	IBuffer* Device::CreateBuffer(size_t buffersize, HEAP_TYPE type, D3D12_RESOURCE_STATES state) {
		CD3DX12_HEAP_PROPERTIES prop = {};
		if (type == HEAP_TYPE::DEFAULT) {
			prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		}
		else {
			prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		}
		Microsoft::WRL::ComPtr<ID3D12Resource> myBuffer;
		m_Device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(buffersize),
			state,
			nullptr,
			IID_PPV_ARGS(&myBuffer));
		return new Buffer(myBuffer.Get());
	}

	ICommandList* Device::CreateCommandList(COMMAND_LIST_TYPE type) {
		D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		if (type == COMMAND_LIST_TYPE::COMPUTE) {
			_type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		}
		else if (type == COMMAND_LIST_TYPE::COPY) {
			_type = D3D12_COMMAND_LIST_TYPE_COPY;
		}
		return new CommandList(m_Device.Get(), _type);
	}
	ICommandQueue* Device::CreateCommandQueue(COMMAND_LIST_TYPE type) {
		D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		if (type == COMMAND_LIST_TYPE::COMPUTE) {
			_type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		}
		else if (type == COMMAND_LIST_TYPE::COPY) {
			_type = D3D12_COMMAND_LIST_TYPE_COPY;
		}
		return new CommandQueue(m_Device.Get(), _type);
	}

	FCCS_API IDevice* CreateDevice() {
		static IDevice* ptr = new Device;
		return ptr;
	}
}