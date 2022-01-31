#include "device.h"
#include "cmd.h"
#include "dx12_backend.h"

namespace SmartFCCS {
	Device::Device() {
		CheckDXError(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device)));
	}

	ICommandList* Device::CreateCommandList(COMMAND_LIST_TYPE type) {
		D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		if (type == COMMAND_LIST_TYPE::COMPUTE) {
			_type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		}
		else if (type == COMMAND_LIST_TYPE::COPY) {
			_type = D3D12_COMMAND_LIST_TYPE_COPY;
		}
		return new CommandList(m_Device.Get(), _type);
	}
	ICommandQueue* Device::CreateCommandQueue(COMMAND_LIST_TYPE type) {
		D3D12_COMMAND_LIST_TYPE _type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		if (type == COMMAND_LIST_TYPE::COMPUTE) {
			_type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		}
		else if (type == COMMAND_LIST_TYPE::COPY) {
			_type = D3D12_COMMAND_LIST_TYPE_COPY;
		}
		return new CommandQueue(m_Device.Get(), _type);
	}

	FCCS_API IDevice* CreateDevice() {
		static IDevice* ptr = new Device;
		return ptr;
	}
}