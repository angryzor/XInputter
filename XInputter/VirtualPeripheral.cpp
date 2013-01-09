#include "StdAfx.h"
#include "VirtualPeripheral.h"
#include <sstream>

VirtualPeripheral::VirtualPeripheral(const std::string& devName) : devName_(devName)
{
	ResetData();
}

VirtualPeripheral::~VirtualPeripheral(void)
{
}

void VirtualPeripheral::ResetData()
{
	memset(&state_,0,sizeof(XINPUT_STATE));
	caps_.Type = XINPUT_DEVTYPE_GAMEPAD;
	caps_.SubType = XINPUT_DEVSUBTYPE_GAMEPAD;
	caps_.Flags = 0;
	caps_.Gamepad.wButtons = XINPUT_GAMEPAD_START | XINPUT_GAMEPAD_BACK | XINPUT_GAMEPAD_LEFT_THUMB | XINPUT_GAMEPAD_RIGHT_THUMB | XINPUT_GAMEPAD_LEFT_SHOULDER 
		| XINPUT_GAMEPAD_RIGHT_SHOULDER | XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_Y;
	caps_.Gamepad.bLeftTrigger = 255;
	caps_.Gamepad.bRightTrigger = 255;
	caps_.Gamepad.sThumbLX = 32767;
	caps_.Gamepad.sThumbLY = 32767;
	caps_.Gamepad.sThumbRX = 32767;
	caps_.Gamepad.sThumbRY = 32767;
	caps_.Vibration.wLeftMotorSpeed = 0;
	caps_.Vibration.wRightMotorSpeed = 0;
}

const std::string& VirtualPeripheral::GetDevName() const
{
	return devName_;
}

std::string VirtualPeripheral::MakeDevName(const std::string& name, int idx)
{
	std::ostringstream oss;
	oss << name << idx;
	return oss.str();
}

DWORD VirtualPeripheral::GetState(XINPUT_STATE* pState) {
	memcpy(pState,&state_,sizeof(XINPUT_STATE));
	return ERROR_SUCCESS;
}

DWORD VirtualPeripheral::SetState(XINPUT_VIBRATION* pVibration) {
	return ERROR_SUCCESS;
}

DWORD VirtualPeripheral::GetCaps(DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities) {
	memcpy(pCapabilities,&caps_,sizeof(XINPUT_CAPABILITIES));
	return ERROR_SUCCESS;
}

void VirtualPeripheral::Enable(BOOL enable) {
	return;
}

