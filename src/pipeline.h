#pragma once
#include <SmartFCCS/RHI.h>
#include <wrl/client.h>
namespace SmartFCCS {
	struct PipelineState: public IPipelineState
	{
		PipelineState(ID3D12PipelineState* pPSO, ID3D12RootSignature* pRoot) :m_PSO(pPSO), m_Root(pRoot) {}

		IUnknown* GetNativePtr() const noexcept {
			return m_PSO.Get();
		}
		ID3D12RootSignature* GetRootSignature() { return m_Root.Get(); }
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PSO;
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_Root;
	};
}