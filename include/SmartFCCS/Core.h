#pragma once

#ifdef FCCS_LIBRARY
#define FCCS_API __declspec(dllexport)
#else
#define FCCS_API __declspec(dllimport)
#endif // FCCS_LIBRARY
#include <Windows.h>

#include <DirectXMath.h>

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>

#include <memory>

#include <cstdint>
#include <cstddef>

namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	FCCS_API void DestroyObject(IObject* object);
}
