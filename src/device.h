#pragma once
#include <SmartFCCS/SmartFCCS.h>
#include <wrl/client.h>
namespace SmartFCCS {
	struct Device : public IDevice
	{
		IUnknown* GetCOMPtr() const noexcept {
			return m_Device.Get();
		}
		Microsoft::WRL::ComPtr<ID3D12Device8> m_Device;
	};
}
