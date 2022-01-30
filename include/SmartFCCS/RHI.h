#pragma once
#include "Core.h"
#include <d3d12.h>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	enum class COMMAND_LIST_TYPE {
		GRAPHICS,
		COMPUTE,
		COPY
	};

	struct ICommandList : public IDXObject {
		virtual void Open() = 0;
		virtual void Close() = 0;
	};

	struct ICommandQueue : public IDXObject {
		virtual void Execute(ICommandList* pList) = 0;
	};

	struct IDevice : public IDXObject {
		
	};

	FCCS_API IDevice* CreateDevice();
}