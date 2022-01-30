#pragma once
#include "Core.h"
#include <d3d12.h>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	struct IDevice : public IDXObject {
		
	};

	FCCS_API IDevice* CreateDevice();
}