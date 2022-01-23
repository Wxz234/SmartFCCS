#pragma once
#include <SmartFCCS/SmartFCCS.h>
#include <wrl/client.h>
namespace SmartFCCS {
	struct Device : public IDevice
	{
		Device();
		IUnknown* GetNativePtr() const noexcept {
			return m_Device.Get();
		}
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
	};
}
