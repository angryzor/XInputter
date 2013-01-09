#include "VirtualX360Controller.h"
#include "IniFile.h"

VirtualX360Controller::VirtualX360Controller(int joyIdx): VirtualPeripheral(MakeDevName("XPad",joyIdx))
{
	if(refCount == 0) {
		DWORD lol;
		realxinput_ = LoadLibrary(TEXT("C:\\Windows\\System32\\XInput1_3.dll"));
		if(!realxinput_)
			lol =GetLastError();
		xigs_ = (XIGS)GetProcAddress(realxinput_,"XInputGetState");
		xiss_ = (XISS)GetProcAddress(realxinput_,"XInputSetState");
		xigc_ = (XIGC)GetProcAddress(realxinput_,"XInputGetCapabilities");
		xie_  = (XIE) GetProcAddress(realxinput_,"XInputEnable");
	}

	refCount++;

	channel_ = CIniFile::GetUIntValue("Channel",GetDevName(),CONFIG_INI_NAME) - 1;
}

DWORD VirtualX360Controller::GetState(XINPUT_STATE* pState)
{
	return xigs_(channel_,pState);
}

DWORD VirtualX360Controller::SetState(XINPUT_VIBRATION* pVibration)
{
	return xiss_(channel_,pVibration);
}

DWORD VirtualX360Controller::GetCaps(DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
	return xigc_(channel_,dwFlags,pCapabilities);
}

void VirtualX360Controller::Enable(BOOL enable)
{
	xie_(enable);
}

VirtualX360Controller::~VirtualX360Controller(void)
{
	refCount--;
	if(refCount == 0)
		FreeLibrary(realxinput_);
}
int VirtualX360Controller::refCount = 0;
HMODULE VirtualX360Controller::realxinput_ = NULL;
VirtualX360Controller::XIGS VirtualX360Controller::xigs_ = NULL;
VirtualX360Controller::XISS VirtualX360Controller::xiss_ = NULL;
VirtualX360Controller::XIGC VirtualX360Controller::xigc_ = NULL;
VirtualX360Controller::XIE VirtualX360Controller::xie_ = NULL;
