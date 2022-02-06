#include "swapchain.h"
#include "window.h"

namespace SmartFCCS {
	SwapChain::SwapChain(IWindow* pWindow, IDevice *pDevice,DXGI_FORMAT format) {
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice;
		auto g_pd3dDevice = (ID3D11Device*)pDevice->GetNativePointer();
		g_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pDXGIDevice));

		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter;
		pDXGIDevice->GetAdapter(&pDXGIAdapter);

		Microsoft::WRL::ComPtr<IDXGIFactory7> pIDXGIFactory;
		pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pIDXGIFactory);

		Window* window = (Window*)pWindow;

		DXGI_SWAP_CHAIN_DESC1 _desc = {};
		_desc.BufferCount = 1;
		_desc.Width = window->w;
		_desc.Height = window->h;
		_desc.Format = format;
		_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		_desc.SampleDesc.Count = 1;
		_desc.SampleDesc.Quality = 0;
		_desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		_desc.Scaling = DXGI_SCALING_STRETCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;
		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		pIDXGIFactory->CreateSwapChainForHwnd(g_pd3dDevice, window->m_Hwnd, &_desc, &fsSwapChainDesc, nullptr, &swapChain);
		pIDXGIFactory->MakeWindowAssociation(window->m_Hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);
		swapChain.As(&m_SwapChain);
	}

	void SwapChain::Present() {
		m_SwapChain->Present(1, 0);
	}

	FCCS_API SwapChainUniquePtr CreateSwapChain(IWindow* pWindow, IDevice* pDevice, DXGI_FORMAT format) {
		return SwapChainUniquePtr(new SwapChain(pWindow, pDevice, format), [](ISwapChain* p) { DestroyObject(p); });
	}
}