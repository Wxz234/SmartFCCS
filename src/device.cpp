#include "device.h"
#include "dx12_backend.h"
namespace SmartFCCS {
	Device::Device() {
		createD3D12Device(&m_Device);
	}
	IDevice* CreateDevice() {
		static Device* ptr = new Device;
		return ptr;
	}
}