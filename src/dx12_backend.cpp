#include "dx12_backend.h"
#include "thirdparty.h"
#include <wrl/client.h>
#include <dxcapi.h>
namespace SmartFCCS {
	void createD3D12Device(ID3D12Device** ppDevice) {
		*ppDevice = nullptr;
		auto mod = getD3D12Module();
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

	void reflectHLSL2RootSignature() {

	}

}