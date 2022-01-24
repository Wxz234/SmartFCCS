#include "dx12_backend.h"
namespace SmartFCCS {
	void CheckDXError(HRESULT hr) {
		if (hr != S_OK) {
			throw "DX ERROR!";
		}
	}

	void ReflectHLSL2RootSignature(D3D12_SHADER_BYTECODE VS, D3D12_SHADER_BYTECODE PS, ID3D12RootSignature** ppRootSignature) {

	}
}