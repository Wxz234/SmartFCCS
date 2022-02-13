#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {

	struct DeviceContext : public IDeviceContext {
		DeviceContext(ID3D11DeviceContext*pDeviceContext) : m_DeviceContext(pDeviceContext) {}
		IUnknown* GetNativePointer() const noexcept { return m_DeviceContext.Get(); }
		void UpdateBuffer(IBuffer* pBuffer, const void* pData, size_t num) {
			D3D11_MAPPED_SUBRESOURCE mappedData = {};
			m_DeviceContext->Map((ID3D11Resource*)pBuffer->GetNativePointer(), 0, D3D11_MAP_WRITE, 0, &mappedData);
			memcpy(mappedData.pData, pData, num);
			m_DeviceContext->Unmap((ID3D11Resource*)pBuffer->GetNativePointer(), 0);
		}
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};

	struct Device : public IDevice {
		Device();
		IUnknown* GetNativePointer() const noexcept { return m_Device.Get(); }
		DeviceContextUniquePtr CreateDeviceContext() { 
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
			m_Device->CreateDeferredContext(0, &deviceContext);
			return DeviceContextUniquePtr(new DeviceContext(deviceContext.Get()), [](IDeviceContext* p) { DestroyObject(p); });
		}
		DeviceContextUniquePtr GetDefaultDeviceContext() const noexcept { return DeviceContextUniquePtr(new DeviceContext(m_DeviceContext.Get()), [](IDeviceContext* p) { DestroyObject(p); }); }
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};
}