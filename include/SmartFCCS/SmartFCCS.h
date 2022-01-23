#pragma once
#include <d3d12.h>
#include <vector>
#include <cstdint>
namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	enum class FORMAT : uint8_t
	{
		UNKNOWN = 0,
		RGBA8_UNORM
	};

	struct IDevice : public IDXObject {
	};

	IDevice* CreateDevice();
}