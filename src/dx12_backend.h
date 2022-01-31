#pragma once
#include <d3d12.h>
#include <cstdint>
namespace SmartFCCS {
	void CheckDXError(HRESULT hr);
	ID3D12CommandAllocator* getCommandAllocatorInPool(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type);
	void updateBusyAllocator(ID3D12CommandAllocator* pAllocator, ID3D12Fence* pFence, uint64_t submitValue);
	void addCommandAllocatorRefCount();
	void releaseCommandAllocatorRef();
}