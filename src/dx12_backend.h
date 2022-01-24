#pragma once
#include <d3d12.h>
namespace SmartFCCS {
	void CheckDXError(HRESULT hr);
	void ReflectHLSL2RootSignature(D3D12_SHADER_BYTECODE VS, D3D12_SHADER_BYTECODE PS, ID3D12RootSignature** ppRootSignature);
}