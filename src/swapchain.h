#include <SmartFCCS/RHI.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <vector>
#include <cstdint>
#define FCCS_SWAPCHAIN_NUM 3
namespace SmartFCCS {
	struct SwapChain : public ISwapChain {
		SwapChain(IWindow* pWindow, ICommandQueue* pQueue);
		~SwapChain();
		IUnknown* GetNativePtr() const noexcept { return m_SwapChain.Get(); }
		void Present();

		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_queue;
		//sync
		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
		Microsoft::WRL::Wrappers::Event m_event;
		std::vector<uint64_t> m_fenceValues;
		uint32_t m_frameIndex;
	};
}