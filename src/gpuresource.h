#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS{
	struct Buffer : public IBuffer
	{
		Buffer(ID3D12Resource* pBuffer) : m_Buffer(pBuffer), m_memory(nullptr) {}
		virtual IUnknown* GetNativePtr() const noexcept { return m_Buffer.Get(); }
		virtual D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const noexcept { return m_Buffer->GetGPUVirtualAddress(); }
		virtual void Write(void* pResource, size_t n);

		Microsoft::WRL::ComPtr<ID3D12Resource> m_Buffer;
		void* m_memory;
	};

	struct Texture : public ITexture
	{

		Texture(ID3D12Resource* pTexture = nullptr,DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN) : m_Texture(pTexture), m_Format(format) {}
		virtual IUnknown* GetNativePtr() const noexcept { return m_Texture.Get(); }
		virtual D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const noexcept { return m_Texture->GetGPUVirtualAddress(); }
		DXGI_FORMAT GetFormat() const noexcept { return m_Format; }
		Microsoft::WRL::ComPtr<ID3D12Resource> m_Texture;
		DXGI_FORMAT m_Format;

	};
}