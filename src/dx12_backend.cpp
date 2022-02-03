#include "dx12_backend.h"
namespace SmartFCCS {
	void CheckDXError(HRESULT hr) {
		if (hr != S_OK) {
			throw "DX ERROR!";
		}
	}
	namespace Internal {

		struct CmdAllocator {
			ID3D12Fence* fence = nullptr;
			uint64_t submitValue = 0;
			D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
		};
		struct CmdAllocatorPool {
			uint32_t refCount = 0;
			std::mutex mtx;
			std::vector<CmdAllocator> canUseAllocator;
			std::vector<CmdAllocator> busyAllocator;

			ID3D12CommandAllocator* getCanUseAllocatorByDeviceAndType(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type) {
				CmdAllocator tempAlloc = {};
				bool isFound = false;
				std::lock_guard<std::mutex> lck(mtx);
				for (auto iter = canUseAllocator.begin(); iter != canUseAllocator.end(); ++iter) {
					if (iter->type == type) {
						tempAlloc = *iter;
						tempAlloc.cmdAllocator->Reset();
						canUseAllocator.erase(iter);
						isFound = true;
						break;
					}
				}

				if (!isFound) {
					pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&tempAlloc.cmdAllocator));
					tempAlloc.type = type;
				}

				busyAllocator.emplace_back(tempAlloc);
				return busyAllocator.back().cmdAllocator.Get();
			}

			void updateBusyAllocator(ID3D12CommandAllocator* pAllocator, ID3D12Fence* pFence, uint64_t submitValue) {
				std::lock_guard<std::mutex> lck(mtx);

				auto iter = busyAllocator.begin();
				while (iter != busyAllocator.end()) {
					if (iter->cmdAllocator.Get() == pAllocator) {
						iter->fence = pFence;
						iter->submitValue = submitValue;
					}
					if (iter->fence && iter->submitValue != 0 && iter->fence->GetCompletedValue() >= iter->submitValue) {
						canUseAllocator.emplace_back(*iter);
						busyAllocator.erase(iter);
						break;
					}
					++iter;
				}
			}
		};
		
		CmdAllocatorPool cmd_Pool;
		ID3D12CommandAllocator* getCommandAllocatorInPool(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type) {
			return cmd_Pool.getCanUseAllocatorByDeviceAndType(pDevice, type);
		}
		void updateBusyAllocator(ID3D12CommandAllocator* pAllocator, ID3D12Fence* pFence, uint64_t submitValue) {
			cmd_Pool.updateBusyAllocator(pAllocator, pFence, submitValue);
		}
		void addCommandAllocatorRefCount() {
			std::lock_guard<std::mutex> lck(cmd_Pool.mtx);
			cmd_Pool.refCount++;
		}
		void releaseCommandAllocatorRef() {
			std::lock_guard<std::mutex> lck(cmd_Pool.mtx);
			cmd_Pool.refCount--;
			if (cmd_Pool.refCount == 0) {
				cmd_Pool.canUseAllocator.clear();
				cmd_Pool.busyAllocator.clear();
			}
		}
	}

	ID3D12CommandAllocator* getCommandAllocatorInPool(ID3D12Device* pDevice, D3D12_COMMAND_LIST_TYPE type) {
		return Internal::getCommandAllocatorInPool(pDevice, type);
	}
	void updateBusyAllocator(ID3D12CommandAllocator* pAllocator, ID3D12Fence* pFence, uint64_t submitValue) {
		Internal::updateBusyAllocator(pAllocator, pFence, submitValue);
	}
	void addCommandAllocatorRefCount() {
		Internal::addCommandAllocatorRefCount();
	}
	void releaseCommandAllocatorRef() {
		Internal::releaseCommandAllocatorRef();
	}

}