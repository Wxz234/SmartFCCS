#pragma once
#include "Core.h"
#include <d3d12.h>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	struct GraphicsPipelineStateDesc {
		D3D12_SHADER_BYTECODE VS = {};
		D3D12_SHADER_BYTECODE PS = {};
	};

	struct IPipelineState : public IDXObject {
		virtual ID3D12RootSignature* GetRootSignature() = 0;
	};

	struct IDevice : public IDXObject {
		virtual IPipelineState* CreateGraphicsPipelineState(const GraphicsPipelineStateDesc& desc) = 0;
	};

	FCCS_API IDevice* CreateDevice();
}