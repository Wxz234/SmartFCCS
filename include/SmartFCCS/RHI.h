#pragma once
#include "Core.h"
#include "Window.h"
#include <d3d12.h>
#include <dxgiformat.h>
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
		virtual ICommandList* CreateCommandList(COMMAND_LIST_TYPE type) = 0;
		virtual ICommandQueue* CreateCommandQueue(COMMAND_LIST_TYPE type) = 0;
	};

	FCCS_API IDevice* CreateDevice();

	struct ISwapChain : public IDXObject {
		virtual void Present() = 0;
	};

	FCCS_API ISwapChain* CreateSwapChain(IWindow* pWindow, ICommandQueue* pQueue, DXGI_FORMAT format);
}