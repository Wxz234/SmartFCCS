#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct CommandList : public ICommandList {
		CommandList(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type);
		~CommandList();
		IUnknown* GetNativePtr() const noexcept { return m_List.Get(); }
		void ResourceBarrier(IResource* pResource, D3D12_RESOURCE_STATES brfore, D3D12_RESOURCE_STATES after);
		void Open();
		void Close();

		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_temp_allocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_List;
		D3D12_COMMAND_LIST_TYPE m_Type;
	};

	struct CommandQueue : public ICommandQueue {
		CommandQueue(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type);
		~CommandQueue();
		IUnknown* GetNativePtr() const noexcept { return m_Queue.Get(); }
		void Execute(ICommandList* pList);

		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_Queue;
		Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
		Microsoft::WRL::Wrappers::Event m_event;
		uint64_t m_submitValue;
	};
}
