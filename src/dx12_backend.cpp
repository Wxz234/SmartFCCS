#include "dx12_backend.h"
#include <d3dcompiler.h>
#include <dxcapi.h> //todo sm6
#include <wrl/client.h>
namespace SmartFCCS {
	void CheckDXError(HRESULT hr) {
		if (hr != S_OK) {
			throw "DX ERROR!";
		}
	}

	void ReflectHLSL2RootSignature(D3D12_SHADER_BYTECODE VS, D3D12_SHADER_BYTECODE PS, ID3D12RootSignature** ppRootSignature) {
		Microsoft::WRL::ComPtr<ID3D12ShaderReflection> pReflection;
		CheckDXError(D3DReflect(VS.pShaderBytecode, VS.BytecodeLength, IID_PPV_ARGS(&pReflection)));
	
		D3D12_SHADER_DESC shader_desc = {};
		CheckDXError(pReflection->GetDesc(&shader_desc));

		for (int i = 0; i < shader_desc.BoundResources; i++)
		{
			D3D12_SHADER_INPUT_BIND_DESC  resource_desc;
			CheckDXError(pReflection->GetResourceBindingDesc(i, &resource_desc));


			//auto shaderVarName = resource_desc.Name;
			//auto registerSpace = resource_desc.Space;
			//auto resourceType = resource_desc.Type;
			//auto bindPoint = resource_desc.BindPoint;

			//std::cout << "var name is " << shaderVarName << std::endl;
			//std::cout << "type name is " << resourceType << std::endl;
			//std::cout << "bind point is " << bindPoint << std::endl;
			//std::cout << "register space is " << registerSpace << std::endl;

		}
	}
}