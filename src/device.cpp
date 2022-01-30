#include "device.h"
#include "dx12_backend.h"

namespace SmartFCCS {
	Device::Device() {
		CheckDXError(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device)));
	}

	FCCS_API IDevice* CreateDevice() {
		static IDevice* ptr = new Device;
		return ptr;
	}
}