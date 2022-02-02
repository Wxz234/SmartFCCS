#include "swapchain.h"
#include "window.h"
#include "gpuresource.h"
#include "dx12_backend.h"

namespace SmartFCCS {
	SwapChain::SwapChain(IWindow* pWindow, ICommandQueue* pQueue, DXGI_FORMAT format) {
		Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
		Window* window = (Window*)pWindow;
		CheckDXError(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)));
		DXGI_SWAP_CHAIN_DESC1 _desc = {};
		_desc.BufferCount = FCCS_SWAPCHAIN_NUM;
		_desc.Width = window->w;
		_desc.Height = window->h;
		_desc.Format = format;
		_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		_desc.SampleDesc.Count = 1;
		_desc.SampleDesc.Quality = 0;
		_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		_desc.Scaling = DXGI_SCALING_STRETCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = 1;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		CheckDXError(factory->CreateSwapChainForHwnd(pQueue->GetNativePtr(), window->m_Hwnd, &_desc, &fsSwapChainDesc, nullptr, &swapChain));
		CheckDXError(factory->MakeWindowAssociation(window->m_Hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER));
		CheckDXError(swapChain.As(&m_SwapChain));

		m_event.Attach(CreateEventW(nullptr, 0, 0, nullptr));
		m_frameIndex = m_SwapChain->GetCurrentBackBufferIndex();
		m_fenceValues.resize(_desc.BufferCount, 0);

		Microsoft::WRL::ComPtr<ID3D12Device8> _device;
		((ID3D12CommandQueue*)pQueue->GetNativePtr())->GetDevice(IID_PPV_ARGS(&_device));
		CheckDXError(swapChain.As(&m_SwapChain));
		CheckDXError(_device->CreateFence(m_fenceValues[m_frameIndex], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		++m_fenceValues[m_frameIndex];

		m_queue = ((ID3D12CommandQueue*)pQueue->GetNativePtr());
		m_SwapchainFormat = format;
		m_res_ptr = new Texture[FCCS_SWAPCHAIN_NUM];
		for (uint32_t i = 0; i < FCCS_SWAPCHAIN_NUM; ++i) {
			((Texture*)m_res_ptr)[i].m_Format = format;
			Microsoft::WRL::ComPtr<ID3D12Resource> my_Texture;
			m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&my_Texture));
			((Texture*)m_res_ptr)[i].m_Texture = my_Texture;
		}
		
	}

	IResource* SwapChain::GetTexture(uint32_t n) const noexcept {
		return &m_res_ptr[n];
	}
	
	void SwapChain::Present() {
		CheckDXError(m_SwapChain->Present(1, 0));
		const uint64_t currentFenceValue = m_fenceValues[m_frameIndex];
		CheckDXError(m_queue->Signal(m_fence.Get(), currentFenceValue));
		m_frameIndex = m_SwapChain->GetCurrentBackBufferIndex();
		if (m_fence->GetCompletedValue() < m_fenceValues[m_frameIndex]) {
			CheckDXError(m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_event.Get()));
			WaitForSingleObjectEx(m_event.Get(), 0xFFFFFFFF, 0);
		}
		m_fenceValues[m_frameIndex] = currentFenceValue + 1;
	}

	SwapChain::~SwapChain() {
		CheckDXError(m_queue->Signal(m_fence.Get(), m_fenceValues[m_frameIndex]));
		CheckDXError(m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_event.Get()));
		WaitForSingleObjectEx(m_event.Get(), 0xFFFFFFFF, 0);
		++m_fenceValues[m_frameIndex];
	}

	FCCS_API ISwapChain* CreateSwapChain(IWindow* pWindow, ICommandQueue* pQueue, DXGI_FORMAT format) {
		return new SwapChain(pWindow, pQueue, format);
	}
}