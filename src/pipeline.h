#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct PipelineState : public IPipelineState {
		PipelineState(ID3D12PipelineState *pPSO, ID3D12RootSignature *pRootSignature):m_pipelineState(pPSO), m_rootSignature(pRootSignature){}
		IUnknown* GetNativePtr() const noexcept { return m_pipelineState.Get(); }
		ID3D12RootSignature* GetRootSignature() const noexcept { return m_rootSignature.Get(); }
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
	};
}