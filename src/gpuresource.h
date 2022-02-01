#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS{
	struct Buffer : public IBuffer
	{
		Buffer();
		virtual IUnknown* GetNativePtr() const noexcept { return m_Buffer.Get(); }
		virtual D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const noexcept { return m_Buffer->GetGPUVirtualAddress(); }
		virtual void Write(void* pResource, size_t n);

		Microsoft::WRL::ComPtr<ID3D12Resource> m_Buffer;
	};
}