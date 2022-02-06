#pragma once
#include "Core.h"
#include <d3d11_4.h>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePointer() const noexcept = 0; 
	};

	struct IDevice : public IDXObject {
		virtual ID3D11DeviceContext* GetDeviceContext() const noexcept = 0;
	};
	using DeviceUniquePtr = std::unique_ptr<IDevice, void(*)(IDevice*)>;
	FCCS_API DeviceUniquePtr CreateDevice();
}