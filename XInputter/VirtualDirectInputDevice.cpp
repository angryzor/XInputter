#include "VirtualDirectInputDevice.h"

VirtualDirectInputDevice::VirtualDirectInputDevice(const std::string& devName, LPDIRECTINPUTDEVICE8 dev) : dev_(dev), VirtualPeripheral(devName)
{
}

VirtualDirectInputDevice::~VirtualDirectInputDevice(void)
{
}

DWORD VirtualDirectInputDevice::GetState(XINPUT_STATE* pState) {
	Poll();
	return VirtualPeripheral::GetState(pState);
}

void VirtualDirectInputDevice::Enable(BOOL enable)
{
	VirtualPeripheral::Enable(enable);
	if(enable) {
		Prepare();
		Acq();
	}
}

void VirtualDirectInputDevice::Acq()
{
	dev_->Acquire();
}

void VirtualDirectInputDevice::UnAcq()
{
	dev_->Unacquire();
}

