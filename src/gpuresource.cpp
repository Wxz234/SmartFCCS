#include "gpuresource.h"
#include "dx12_backend.h"
namespace SmartFCCS {
	void Buffer::Write(void* pResource, size_t n) {
		CheckDXError(m_Buffer->Map(0, nullptr, &m_memory));
		memcpy(m_memory, pResource, n);
		m_Buffer->Unmap(0, nullptr);
	}
}
