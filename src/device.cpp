#include "device.h"

namespace SmartFCCS {
	Device::Device() {
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device));
	}
}