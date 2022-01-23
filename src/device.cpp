#include "device.h"
#include "d3dx12.h"
namespace SmartFCCS {



	IDevice* CreateDevice() {
		static Device* ptr = new Device;
		return ptr;
	}
}