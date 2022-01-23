#include "device.h"
namespace SmartFCCS {

	IDevice* CreateDevice() {
		static Device* ptr = new Device;
		return ptr;
	}
}