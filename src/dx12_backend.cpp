#include "dx12_backend.h"
#include <wrl/client.h>
namespace SmartFCCS {
	void createD3D12Device(ID3D12Device** ppDevice) {
		*ppDevice = nullptr;
		static auto mod = LoadLibraryW(L"d3d12.dll");
		auto createDevice = (PFN_D3D12_CREATE_DEVICE)GetProcAddress(mod, "D3D12CreateDevice");
		Microsoft::WRL::ComPtr<ID3D12Device> device;
		createDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
		*ppDevice = device.Detach();
	}

	DXGI_FORMAT GetDXGI_FORMAT(FORMAT format) {
		if (format == FORMAT::UNKNOWN) {
			return DXGI_FORMAT_UNKNOWN;
		}
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}

	struct CmdAllocator {};

}