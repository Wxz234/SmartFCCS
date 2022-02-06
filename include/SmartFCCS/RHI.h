#pragma once
#include "Core.h"
#include <d3d11_4.h>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePointer() const noexcept = 0; 
	};

	struct IDevice : public IDXObject {

	};
}