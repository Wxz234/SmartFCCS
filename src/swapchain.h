#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct SwapChain : public ISwapChain {
		SwapChain(IWindow* pWindow, IDevice* pDevic,DXGI_FORMAT format);
		//~SwapChain();
		ID3D11RenderTargetView* GetRenderTargetView() const noexcept;
		IUnknown* GetNativePointer() const noexcept { return m_SwapChain.Get(); }
		void Present();

		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	};
}