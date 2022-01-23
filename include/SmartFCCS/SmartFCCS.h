#pragma once
#include <d3d12.h>
#include <vector>
#include <cstdint>
namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	struct ID3DObject : public IObject {
		virtual IUnknown* GetD3DPtr() const noexcept = 0;
	};

	enum class FORMAT : uint8_t
	{
		UNKNOWN = 0,
		RGBA8_UNORM
	};
	
	struct GraphicsPipelineDesc {
		D3D12_SHADER_BYTECODE VS = {};
		D3D12_SHADER_BYTECODE PS = {};
		uint32_t NumRenderTargets = 0;
		FORMAT RTVFormats[8] = {};
		D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	};
	struct IPipeline : public ID3DObject {

	};
	struct IDevice : public ID3DObject {
		virtual IPipeline* CreateGraphicsPipeline(const GraphicsPipelineDesc& desc) = 0;
	};

	IDevice* CreateDevice();
}