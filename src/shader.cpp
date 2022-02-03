#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	std::string gettarget(SHADER_MODEL sm, SHADER_TYPE type) {
		std::string temp;
		if (type == SHADER_TYPE::VERTEX) {
			temp += "vs";
		}
		else {
			temp += "ps";
		}

		if (sm == SHADER_MODEL::SM_5_0) {
			temp += "_5_0";
		}
		else {
			temp += "_5_1";
		}
		return temp;
	}

	FCCS_API HRESULT CompileShaderFromFile(const wchar_t* filename, const D3D_SHADER_MACRO* pDefines, const char* entry, SHADER_MODEL sm, SHADER_TYPE type, ID3DBlob** ppvBlob) {
		auto target_str = gettarget(sm, type);
		return D3DCompileFromFile(filename, pDefines, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry, target_str.c_str(), 0, 0, ppvBlob, nullptr);
	}
}