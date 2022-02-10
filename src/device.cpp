#include "device.h"
#include "buffer.h"
namespace SmartFCCS {
	Device::Device() {
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, 2, D3D11_SDK_VERSION, m_Device.GetAddressOf(), nullptr, m_DeviceContext.GetAddressOf());
	}

	HRESULT Device::CreateInputLayout(uint32_t inputSlot,const void* pShaderBytecodeWithInputSignature, size_t BytecodeLength, ID3D11InputLayout** ppInputLayout) {
		Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;
		D3DReflect(pShaderBytecodeWithInputSignature, BytecodeLength, IID_PPV_ARGS(&reflection));

		D3D11_SHADER_DESC t_ShaderDesc = {};
		reflection->GetDesc(&t_ShaderDesc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> t_InputElementDescVec;
		uint32_t t_ByteOffset = 0;

		for (uint32_t i = 0; i != t_ShaderDesc.InputParameters; ++i) {
			D3D11_SIGNATURE_PARAMETER_DESC t_SP_DESC = {};
			reflection->GetInputParameterDesc(i, &t_SP_DESC);

			D3D11_INPUT_ELEMENT_DESC t_InputElementDesc = {};
			t_InputElementDesc.SemanticName = t_SP_DESC.SemanticName;
			t_InputElementDesc.SemanticIndex = t_SP_DESC.SemanticIndex;
			t_InputElementDesc.InputSlot = inputSlot;
			t_InputElementDesc.AlignedByteOffset = t_ByteOffset;
			t_InputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			t_InputElementDesc.InstanceDataStepRate = 0;

			if (t_SP_DESC.Mask == 1) {
				if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32_UINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32_SINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32_FLOAT;
				}
				t_ByteOffset += 4;
			}
			else if (t_SP_DESC.Mask <= 3) {
				if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
				}
				t_ByteOffset += 8;
			}
			else if (t_SP_DESC.Mask <= 7) {
				if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				}
				t_ByteOffset += 12;
			}
			else if (t_SP_DESC.Mask <= 15) {
				if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				}
				else if (t_SP_DESC.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {
					t_InputElementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				}
				t_ByteOffset += 16;
			}

			t_InputElementDescVec.emplace_back(t_InputElementDesc);
		}

		return m_Device->CreateInputLayout(t_InputElementDescVec.data(), t_InputElementDescVec.size(), pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
	}

	FCCS_API DeviceUniquePtr CreateDevice() {
		return DeviceUniquePtr(new Device, [](IDevice* p) { DestroyObject(p); });
	}
}