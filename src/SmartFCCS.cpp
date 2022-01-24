#include <SmartFCCS/Core.h>
namespace SmartFCCS {
	IObject::~IObject() {}
	void DestroyObject(IObject* object) {
		delete object;
	}

}