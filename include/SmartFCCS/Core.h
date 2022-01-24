#pragma once

#ifdef FCCS_LIBRARY
#define FCCS_API __declspec(dllexport)
#elif
#define FCCS_API __declspec(dllimport)
#endif // FCCS_LIBRARY

namespace SmartFCCS {
	struct IObject {
		virtual ~IObject();
	};
	FCCS_API void DestroyObject(IObject* object);
}
