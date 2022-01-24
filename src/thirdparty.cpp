#include "thirdparty.h"

namespace SmartFCCS {
	HMODULE getDXCompilerModule() {
		static auto mod = LoadLibraryW(L"d3dcompiler_47.dll");
		return mod;
	}
	HMODULE getD3D12Module() {
		static auto mod = LoadLibraryW(L"d3d12.dll");
		return mod;
	}

}