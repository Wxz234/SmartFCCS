#pragma once
#include <SmartFCCS/SmartFCCS.h>

namespace SmartFCCS {
	void createD3D12Device(ID3D12Device** ppDevice);
	void reflectHLSL2RootSignature();
}