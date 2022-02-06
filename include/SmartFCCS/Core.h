#pragma once

#ifdef FCCS_LIBRARY
#define FCCS_API __declspec(dllexport)
#else
#define FCCS_API __declspec(dllimport)
#endif // FCCS_LIBRARY
#include <memory>
namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	FCCS_API void DestroyObject(IObject* object);
}
