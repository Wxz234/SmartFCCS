#include "cmd.h"
#include "dx12_backend.h"
#include <synchapi.h>
namespace SmartFCCS {
	CommandList::CommandList(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type) {
		m_Device = pDevice;
		m_Type = type;
		ID3D12Device8* device8 = nullptr;
		CheckDXError(m_Device->QueryInterface(&device8));
		CheckDXError(device8->CreateCommandList1(0, type, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&m_List)));
		device8->Release();

		addCommandAllocatorRefCount();
	}

	CommandList::~CommandList() {
		releaseCommandAllocatorRef();
	}

	void CommandList::Open() {
		m_temp_allocator = getCommandAllocatorInPool(m_Device.Get(), m_Type);
		CheckDXError(m_List->Reset(m_temp_allocator.Get(), nullptr));
	}

	void CommandList::Close() {
		CheckDXError(m_List->Close());
	}

	CommandQueue::CommandQueue(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type) {
		m_Device = pDevice;
		CheckDXError(m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Type = type;
		CheckDXError(m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_Queue)));
		m_event.Attach(CreateEventW(0, 0, 0, 0));
		m_submitValue = 0;

		addCommandAllocatorRefCount();
	}

	CommandQueue::~CommandQueue() {
		m_submitValue++;
		CheckDXError(m_Queue->Signal(m_fence.Get(), m_submitValue));
		CheckDXError(m_fence->SetEventOnCompletion(m_submitValue, m_event.Get()));
		WaitForSingleObjectEx(m_event.Get(), INFINITE, FALSE);
		releaseCommandAllocatorRef();
	}


	void CommandQueue::Execute(ICommandList* pList) {
		ID3D12CommandList* pLists[] = { (ID3D12CommandList*)pList->GetNativePtr() };
		m_Queue->ExecuteCommandLists(1, pLists);
		m_submitValue++;
		CheckDXError(m_Queue->Signal(m_fence.Get(), m_submitValue));

		auto cmdlist = (CommandList*)pList;
		updateBusyAllocator(cmdlist->m_temp_allocator.Get(), m_fence.Get(), m_submitValue);
	}
}