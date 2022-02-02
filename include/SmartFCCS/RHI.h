#pragma once
#include "Core.h"
#include "Window.h"
#include <d3d12.h>
#include <dxgiformat.h>
#include <d3dcommon.h>
#include <cstddef>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	enum class HEAP_TYPE {
		DEFAULT,
		UPLOAD
	};

	struct IResource : public IDXObject {
		virtual D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const noexcept = 0;
	};

	struct ITexture : public IResource {
		virtual DXGI_FORMAT GetFormat() const noexcept = 0;
	};

	struct IBuffer : public IResource {
		virtual void Write(void* pResource, size_t n) = 0;
	};

	enum class COMMAND_LIST_TYPE {
		GRAPHICS,
		COMPUTE,
		COPY
	};

	struct ICommandList : public IDXObject {
		virtual void ResourceBarrier(IResource* pResource, D3D12_RESOURCE_STATES brfore, D3D12_RESOURCE_STATES after) = 0;
		virtual void Open() = 0;
		virtual void Close() = 0;
	};

	struct ICommandQueue : public IDXObject {
		virtual void Execute(ICommandList* pList) = 0;
	};

	struct IDevice : public IDXObject {
		virtual IBuffer* CreateBuffer(HEAP_TYPE type, D3D12_RESOURCE_STATES state, size_t buffersize) = 0;
		virtual HRESULT CreateRootSignature(const D3D12_ROOT_SIGNATURE_DESC* pRootSignature, ID3D12RootSignature** ppvRootSignature) = 0;
		virtual ICommandList* CreateCommandList(COMMAND_LIST_TYPE type) = 0;
		virtual ICommandQueue* CreateCommandQueue(COMMAND_LIST_TYPE type) = 0;
	};

	FCCS_API IDevice* CreateDevice();

	struct ISwapChain : public IDXObject {
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView(uint32_t n) const noexcept = 0;
		virtual ITexture* GetTexture(uint32_t n) const noexcept = 0;
		virtual uint32_t GetFrameIndex() const noexcept = 0;
		virtual void Present() = 0;
	};

	FCCS_API ISwapChain* CreateSwapChain(IWindow* pWindow, ICommandQueue* pQueue, DXGI_FORMAT format);

	enum class SHADERMODEL {
		SM_5_0,
		SM_5_1
	};

	enum class SHADERTYPE {
		VERTEX,
		PIXEL
	};

	FCCS_API HRESULT CompileShaderFromFile(const wchar_t* filename, const D3D_SHADER_MACRO* pDefines, const char* entry, SHADERMODEL sm, SHADERTYPE type, ID3DBlob** ppvBlob);
}