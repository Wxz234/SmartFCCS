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

	struct GRAPHICS_PIPELINE_DESC {
		ID3D12RootSignature* pRootSignature = nullptr;
		D3D12_SHADER_BYTECODE VS = {};
		D3D12_SHADER_BYTECODE PS = {};
		D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		D3D12_INPUT_LAYOUT_DESC InputLayout = { nullptr ,0 };
		UINT NumRenderTargets = 0;
		DXGI_FORMAT RTVFormats[8] = { DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN ,DXGI_FORMAT_UNKNOWN };
		DXGI_FORMAT DSVFormat = DXGI_FORMAT_UNKNOWN;

		D3D12_VIEWPORT Viewport = { 0.f, 0.f, 0.f, 0.f, 0.f, 1.f };
		D3D12_RECT Scissor = { 0, 0, 0, 0 };
	};

	struct IPipelineState : public IDXObject {
		virtual ID3D12RootSignature* GetRootSignature() const noexcept = 0;
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
		virtual void SetGraphicsPipelineState(IPipelineState* pPipelineState) = 0;
		virtual void ResourceBarrier(IResource* pResource, D3D12_RESOURCE_STATES brfore, D3D12_RESOURCE_STATES after) = 0;
		virtual void Open() = 0;
		virtual void Close() = 0;
	};

	struct ICommandQueue : public IDXObject {
		virtual void WaitIdle() = 0;
		virtual void Execute(ICommandList* pList) = 0;
	};

	struct IDevice : public IDXObject {
		virtual IPipelineState* CreateGraphicsPipelineState(const GRAPHICS_PIPELINE_DESC* pDesc) = 0;
		virtual ITexture* CreateTexture(uint32_t width, uint32_t height, uint32_t levels, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flag, const D3D12_CLEAR_VALUE* pOptimizedClearValue, D3D12_RESOURCE_STATES state) = 0;
		virtual IBuffer* CreateBuffer(size_t buffersize, HEAP_TYPE type, D3D12_RESOURCE_STATES state) = 0;
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

	enum class SHADER_MODEL {
		SM_5_0,
		SM_5_1
	};

	enum class SHADER_TYPE {
		VERTEX,
		PIXEL
	};

	FCCS_API HRESULT CompileShaderFromFile(const wchar_t* filename, const D3D_SHADER_MACRO* pDefines, const char* entry, SHADER_MODEL sm, SHADER_TYPE type, ID3DBlob** ppvBlob);
}