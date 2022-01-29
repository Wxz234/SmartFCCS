#pragma once
#include <SmartFCCS/RHI.h>
#include <wrl/client.h>
namespace SmartFCCS {
	struct Device : public IDevice
	{
		Device();
		IUnknown* GetNativePtr() const noexcept {
			return m_Device.Get();
		}

		IPipelineState* CreateGraphicsPipelineState(const GraphicsPipelineStateDesc& desc);
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
	};
}
