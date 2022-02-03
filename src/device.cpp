#include "device.h"
#include "cmd.h"
#include "gpuresource.h"
#include "dx12_backend.h"
namespace SmartFCCS {
	Device::Device() {
		CheckDXError(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device)));
	}

	IPipelineState* Device::CreateGraphicsPipelineState(const GRAPHICS_PIPELINE_DESC* pDesc) {
		return nullptr;
	}

	HRESULT Device::CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, ID3D12RootSignature** ppvRootSignature) {
		Microsoft::WRL::ComPtr<ID3DBlob> signature;
		Microsoft::WRL::ComPtr<ID3DBlob> error;
		CheckDXError(D3D12SerializeRootSignature(pRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		return m_Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(ppvRootSignature));
	}

	IBuffer* Device::CreateBuffer(HEAP_TYPE type, D3D12_RESOURCE_STATES state, size_t buffersize) {
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