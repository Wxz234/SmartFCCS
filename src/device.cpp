#include "device.h"
#include "d3dx12.h"
namespace SmartFCCS {

	IPipeline* Device::CreateGraphicsPipeline(const GraphicsPipelineDesc& desc) {
		D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d_desc = {};
		d3d_desc.VS = desc.VS;
		d3d_desc.PS = desc.PS;
        //psoDesc.pRootSignature = m_rootSignature.Get();
        d3d_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        d3d_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        d3d_desc.DepthStencilState.DepthEnable = FALSE;
        d3d_desc.DepthStencilState.StencilEnable = FALSE;
        d3d_desc.SampleMask = 0xffffffff;
        d3d_desc.PrimitiveTopologyType = desc.PrimitiveTopologyType;
		d3d_desc.NumRenderTargets = desc.NumRenderTargets;
        d3d_desc.SampleDesc.Count = 1;
		return nullptr;
	}

	IDevice* CreateDevice() {
		static Device* ptr = new Device;
		return ptr;
	}
}