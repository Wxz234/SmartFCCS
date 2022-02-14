#pragma once
#include "pch.h"
#include <SmartFCCS/RHI.h>
namespace SmartFCCS {
	struct Buffer : public IBuffer {
		Buffer(ID3D11Buffer* pBuffer){
			m_buffer = pBuffer;
			m_buffer->GetDesc(&m_Desc);
		}
		IUnknown* GetNativePointer() const noexcept { return m_buffer.Get(); }
		D3D11_BUFFER_DESC* GetDesc() {
			return &m_Desc;
		}

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
		D3D11_BUFFER_DESC m_Desc;
	};
}