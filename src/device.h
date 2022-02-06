#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct Device : public IDevice {
		Device();
		IUnknown* GetNativePointer() const noexcept { return m_Device.Get(); }
		ID3D11DeviceContext* GetDeviceContext() const noexcept { return m_DeviceContext.Get(); }
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};
}