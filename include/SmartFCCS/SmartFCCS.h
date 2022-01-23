#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <cstdint>
#include <dxgiformat.h>
namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	void DestroyObject(IObject* object);

	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	enum class FORMAT : uint8_t
	{
		UNKNOWN = 0,
		RGBA8_UNORM
	};
	DXGI_FORMAT GetDXGI_FORMAT(FORMAT format);

	struct IDevice : public IDXObject {
	};

	IDevice* CreateDevice();

	struct IWindow : public IObject {

	};
	IWindow* CreateFCCSWindow();
}