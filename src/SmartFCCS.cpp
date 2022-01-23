#include <SmartFCCS/SmartFCCS.h>
namespace SmartFCCS {
	IObject::~IObject(){}
	void DestroyObject(IObject* object) {
		delete object;
	}

}