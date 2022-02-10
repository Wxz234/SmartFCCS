#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {

	struct DeviceContext : public IDeviceContext {
		DeviceContext(ID3D11DeviceContext*pDeviceContext) : m_DeviceContext(pDeviceContext) {}
		IUnknown* GetNativePointer() const noexcept { return m_DeviceContext.Get(); }

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};

	struct Device : public IDevice {
		Device();
		IUnknown* GetNativePointer() const noexcept { return m_Device.Get(); }
		DeviceContextUniquePtr GetDefaultDeviceContext() const noexcept { return DeviceContextUniquePtr(new DeviceContext(m_DeviceContext.Get()), [](IDeviceContext* p) { DestroyObject(p); }); }
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};
}