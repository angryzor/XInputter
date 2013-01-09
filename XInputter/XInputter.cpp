// XInputter.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "XInputter.h"
#include <dinput.h>
#include <XInput.h>
#include "VirtualController.h"
#include "VirtualKeyboard.h"
#include "VirtualX360Controller.h"
#include "IniFile.h"
#include "IsXInput.h"

HINSTANCE hInst = NULL;
LPDIRECTINPUT8 di = NULL;
LPDIRECTINPUTDEVICE8 dev = NULL;
const int maxdevs = 4;
unsigned int idx = 1;
unsigned int numkeybs;
unsigned int numjoys;
unsigned int numxpads;
vpvec vps;
bool booted = false;

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE*     
                                       pdidInstance, VOID* pContext)
{
	HRESULT hr;
	if(idx > numjoys || vps.size() >= maxdevs)
		return DIENUM_STOP;

	if( IsXInputDevice( &pdidInstance->guidProduct )) 
		return DIENUM_CONTINUE;

    // Obtain an interface to the enumerated joystick.
    hr = di->CreateDevice(pdidInstance->guidInstance,  
                                &dev, NULL);
    if(FAILED(hr)) 
        return DIENUM_CONTINUE;

	vps.insert(vps.end(),new VirtualController(dev,idx));
	idx++;

	return DIENUM_CONTINUE;
}

void initit() {
	booted = true;
	HRESULT hr;
	numkeybs=CIniFile::GetUIntValue("NumKeybs", "XInputter", CONFIG_INI_NAME);
	numjoys=CIniFile::GetUIntValue("NumJoys", "XInputter", CONFIG_INI_NAME);
	numxpads=CIniFile::GetUIntValue("NumXPads", "XInputter", CONFIG_INI_NAME);

	for(unsigned int i = 0; i < numxpads; i++)
		vps.insert(vps.end(),new VirtualX360Controller(i+1));

	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL);
	if(FAILED(hr))
		throw std::runtime_error("Got problem");

	di->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);

	// Create keybs
	if(numkeybs > 0)
	{
		if(FAILED(di->CreateDevice(GUID_SysKeyboard, &dev, NULL)))
			throw std::runtime_error("Got problem");

		for(unsigned int i = 0; i < numkeybs; i++)
			vps.insert(vps.end(), new VirtualKeyboard(dev, i+1));
	}
		
}

void uninit() {
	for(vpvec::iterator i = vps.begin(); i != vps.end(); i++)
		delete *i;

	di->Release();
}

extern "C" {
DWORD WINAPI XInputGetState
(
    DWORD         dwUserIndex,  // [in] Index of the gamer associated with the device
    XINPUT_STATE* pState        // [out] Receives the current state
)
{
	// For compatibility with older versions of XInput
	if(!booted)
		XInputEnable(true);

	if(dwUserIndex >= vps.size()) return ERROR_DEVICE_NOT_CONNECTED;
	return vps[dwUserIndex]->GetState(pState);
}

DWORD WINAPI XInputSetState
(
    DWORD             dwUserIndex,  // [in] Index of the gamer associated with the device
    XINPUT_VIBRATION* pVibration    // [in, out] The vibration information to send to the controller
)
{
	if(!booted)
		XInputEnable(true);

	if(dwUserIndex >= vps.size()) return ERROR_DEVICE_NOT_CONNECTED;
	return vps[dwUserIndex]->SetState(pVibration);
}

DWORD WINAPI XInputGetCapabilities
(
    DWORD                dwUserIndex,   // [in] Index of the gamer associated with the device
    DWORD                dwFlags,       // [in] Input flags that identify the device type
    XINPUT_CAPABILITIES* pCapabilities  // [out] Receives the capabilities
)
{
	if(!booted)
		XInputEnable(true);

	if(dwUserIndex  >= vps.size()) return ERROR_DEVICE_NOT_CONNECTED;
	return vps[dwUserIndex]->GetCaps(dwFlags, pCapabilities);
}


void WINAPI XInputEnable
(
    BOOL enable     // [in] Indicates whether xinput is enabled or disabled. 
)
{
	if(!booted)initit();
	for(vpvec::iterator i = vps.begin(); i != vps.end(); i++)
		(*i)->Enable(enable);
}
}