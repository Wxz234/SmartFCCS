#include "thirdparty.h"

namespace SmartFCCS {
	HMODULE getDXCModule() {
		static auto mod = LoadLibraryW(L"../thirdparty/dxc/bin/x64/dxcompiler.dll");
		return mod;
	}
	HMODULE getD3D12Module() {
		static auto mod = LoadLibraryW(L"d3d12.dll");
		return mod;
	}

}