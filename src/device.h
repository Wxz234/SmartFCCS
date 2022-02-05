#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct Device : public IDevice
	{
		Device();
		~Device();
		IUnknown* GetNativePtr() const noexcept {
			return m_Device.Get();
		}
		IPipelineState* CreateGraphicsPipelineState(const GRAPHICS_PIPELINE_DESC* pDesc);
		ITexture* CreateDDSTextureFromFile(const wchar_t* filename, D3D12_RESOURCE_STATES state);
		ITexture* CreateTexture(uint32_t width, uint32_t height, uint32_t levels, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* pOptimizedClearValue, D3D12_RESOURCE_STATES state);
		IBuffer* CreateBuffer(size_t buffersize, HEAP_TYPE type, D3D12_RESOURCE_STATES state);
		HRESULT CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, ID3D12RootSignature** ppvRootSignature);

		ICommandList* CreateCommandList(COMMAND_LIST_TYPE type);
		ICommandQueue* CreateCommandQueue(COMMAND_LIST_TYPE type);

		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		ICommandQueue* m_queue;
		ICommandList* m_list;
	};
}
