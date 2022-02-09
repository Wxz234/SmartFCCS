#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct Device : public IDevice {
		Device();
		IUnknown* GetNativePointer() const noexcept { return m_Device.Get(); }
		//RenderTextureUniquePtr CreateRenderTexture(uint32_t width, uint32_t height, DXGI_FORMAT format);
		HRESULT CreateInputLayout(const void* pShaderBytecodeWithInputSignature, size_t BytecodeLength, ID3D11InputLayout** ppInputLayout);
		ID3D11DeviceContext* GetDeviceContext() const noexcept { return m_DeviceContext.Get(); }
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	};
}