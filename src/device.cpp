#include "device.h"
#include "buffer.h"
namespace SmartFCCS {
	Device::Device() {
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, 2, D3D11_SDK_VERSION, m_Device.GetAddressOf(), nullptr, m_DeviceContext.GetAddressOf());
	}

	BufferUniquePtr Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData) {
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		m_Device->CreateBuffer(pDesc, pInitialData, &buffer);
		return BufferUniquePtr(new Buffer(buffer.Get()), [](IBuffer* p) { DestroyObject(p); });
	}

	FCCS_API DeviceUniquePtr CreateDevice() {
		return DeviceUniquePtr(new Device, [](IDevice* p) { DestroyObject(p); });
	}
}