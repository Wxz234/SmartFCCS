#pragma once
#include "Core.h"
#include "Window.h"

namespace SmartFCCS {

	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePointer() const noexcept = 0; 
	};

	struct IRenderTexture : public IDXObject {
		virtual ID3D11ShaderResourceView* GetShaderResourceView() const noexcept = 0;
		virtual ID3D11RenderTargetView* GetRenderTargetView() const noexcept = 0;
	};
	using RenderTextureUniquePtr = std::unique_ptr<IRenderTexture, void(*)(IRenderTexture*)>;

	struct IDevice : public IDXObject {
		virtual ID3D11DeviceContext* GetDeviceContext() const noexcept = 0;
	};
	using DeviceUniquePtr = std::unique_ptr<IDevice, void(*)(IDevice*)>;
	FCCS_API DeviceUniquePtr CreateDevice();

	struct ISwapChain : public IDXObject {
		virtual ID3D11RenderTargetView* GetRenderTargetView() const noexcept = 0;
		virtual void Present() = 0;
	};
	using SwapChainUniquePtr = std::unique_ptr<ISwapChain, void(*)(ISwapChain*)>;
	FCCS_API SwapChainUniquePtr CreateSwapChain(IWindow* pWindow, IDevice* pDevice, DXGI_FORMAT format);
}