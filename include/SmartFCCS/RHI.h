#pragma once
#include "Core.h"
#include <d3d12.h>
namespace SmartFCCS {
	struct IDXObject : public IObject {
		virtual IUnknown* GetNativePtr() const noexcept = 0;
	};

	struct PipelineStateDesc {
		D3D12_SHADER_BYTECODE VS = {};
		D3D12_SHADER_BYTECODE PS = {};
	};

	struct PipelineState : public IDXObject {
		virtual ID3D12RootSignature* GetRootSignature() = 0;
	};

	struct IDevice : public IDXObject {

	};
}