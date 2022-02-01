#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	std::string gettarget(SHADERMODEL sm, SHADERTYPE type) {
		std::string temp;
		if (type == SHADERTYPE::VERTEX) {
			temp += "vs";
		}
		else {
			temp += "ps";
		}

		if (sm == SHADERMODEL::SM_5_0) {
			temp += "_5_0";
		}
		else {
			temp += "_5_1";
		}
		return temp;
	}

	FCCS_API HRESULT CompileShaderFromFile(const wchar_t* filename, const char* entry, SHADERMODEL sm, SHADERTYPE type, ID3DBlob** ppvBlob) {
		auto target_str = gettarget(sm, type);
		return D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry, target_str.c_str(), 0, 0, ppvBlob, nullptr);
	}
}