#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct Device : public IDevice
	{
		Device();
		IUnknown* GetNativePtr() const noexcept {
			return m_Device.Get();
		}
		IBuffer* CreateBuffer(HEAP_TYPE type, D3D12_RESOURCE_STATES state, size_t buffersize);
		HRESULT CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, ID3D12RootSignature** ppvRootSignature);

		ICommandList* CreateCommandList(COMMAND_LIST_TYPE type);
		ICommandQueue* CreateCommandQueue(COMMAND_LIST_TYPE type);

		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
	};
}
