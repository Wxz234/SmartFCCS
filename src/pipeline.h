#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct GraphicsPipelineState : public IPipelineState {
		GraphicsPipelineState(ID3D12PipelineState* pPSO, ID3D12RootSignature* pRootSignature, const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissor) : m_pipelineState(pPSO), m_rootSignature(pRootSignature), m_viewport(viewport), m_Scissor(scissor) {}
		IUnknown* GetNativePtr() const noexcept { return m_pipelineState.Get(); }
		ID3D12RootSignature* GetRootSignature() const noexcept { return m_rootSignature.Get(); }
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;

		D3D12_VIEWPORT m_viewport;
		D3D12_RECT m_Scissor;
	};
}