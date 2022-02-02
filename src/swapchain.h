#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
#define FCCS_SWAPCHAIN_NUM 3
namespace SmartFCCS {
	struct SwapChain : public ISwapChain {
		SwapChain(IWindow* pWindow, ICommandQueue* pQueue, DXGI_FORMAT format);
		~SwapChain();
		IUnknown* GetNativePtr() const noexcept { return m_SwapChain.Get(); }
		ITexture* GetTexture(uint32_t n) const noexcept;
		uint32_t GetFrameIndex() const noexcept { return m_SwapChain->GetCurrentBackBufferIndex(); }
		void Present();

		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_queue;
		//sync
		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
		Microsoft::WRL::Wrappers::Event m_event;
		std::vector<uint64_t> m_fenceValues;
		uint32_t m_frameIndex;
		//
		std::vector<ITexture*> m_tex;
		DXGI_FORMAT m_SwapchainFormat;
	};
}