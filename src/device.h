#pragma once
#include <SmartFCCS/RHI.h>
#include <wrl/client.h>
namespace SmartFCCS {
	struct Device : public IDevice
	{
		Device();
		IUnknown* GetNativePtr() const noexcept {
			return m_Device.Get();
		}

		HRESULT CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, ID3D12RootSignature** ppvRootSignature);

		ICommandList* CreateCommandList(COMMAND_LIST_TYPE type);
		ICommandQueue* CreateCommandQueue(COMMAND_LIST_TYPE type);

		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
	};
}
