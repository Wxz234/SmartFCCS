#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgiformat.h>

#include <cstdint>

#define FCCS_API

namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	FCCS_API void DestroyObject(IObject* object);

	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	enum class FORMAT : uint8_t
	{
		UNKNOWN = 0,
		RGBA8_UNORM
	};
	FCCS_API DXGI_FORMAT GetDXGI_FORMAT(FORMAT format);

	struct IDevice : public IDXObject {
	};

	FCCS_API IDevice* CreateDevice();
}