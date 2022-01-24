#include "dx12_backend.h"
namespace SmartFCCS {
	void CheckDXError(HRESULT hr) {
		if (hr != S_OK) {
			throw "DX ERROR!";
		}
	}
}