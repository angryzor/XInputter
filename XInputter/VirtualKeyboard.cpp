#include "StdAfx.h"
#include "VirtualKeyboard.h"
#include "IniFile.h"


VirtualKeyboard::VirtualKeyboard(LPDIRECTINPUTDEVICE8 dev, int idx) : VirtualDirectInputDevice(MakeDevName("Key",idx),dev)
{
	refCount++;

	std::map<std::string,BYTE> cfgKeys;
    cfgKeys["0"] = DIK_0;
    cfgKeys["1"] = DIK_1;
    cfgKeys["2"] = DIK_2;
    cfgKeys["3"] = DIK_3;
    cfgKeys["4"] = DIK_4;
    cfgKeys["5"] = DIK_5;
    cfgKeys["6"] = DIK_6;
    cfgKeys["7"] = DIK_7;
    cfgKeys["8"] = DIK_8;
    cfgKeys["9"] = DIK_9;
    cfgKeys["A"] = DIK_A;
    cfgKeys["NUMPADADD"] = DIK_ADD;
    cfgKeys["APOSTROPHE"] = DIK_APOSTROPHE;
    cfgKeys["B"] = DIK_B;
    cfgKeys["BACKSPACE"] = DIK_BACKSPACE;
    cfgKeys["BACKSLASH"] = DIK_BACKSLASH;
    cfgKeys["C"] = DIK_C;
    cfgKeys["CAPSLOCK"] = DIK_CAPSLOCK;
    cfgKeys["COMMA"] = DIK_COMMA;
    cfgKeys["D"] = DIK_D;
    cfgKeys["NUMPADPERIOD"] = DIK_DECIMAL;
    cfgKeys["DELETE"] = DIK_DELETE;
    cfgKeys["NUMPADDIV"] = DIK_DIVIDE;
    cfgKeys["DOWN"] = DIK_DOWN;
    cfgKeys["E"] = DIK_E;
    cfgKeys["END"] = DIK_END;
    cfgKeys["EQUALS"] = DIK_EQUALS;
    cfgKeys["ESCAPE"] = DIK_ESCAPE;
    cfgKeys["F"] = DIK_F;
    cfgKeys["F1"] = DIK_F1;
    cfgKeys["F2"] = DIK_F2;
    cfgKeys["F3"] = DIK_F3;
    cfgKeys["F4"] = DIK_F4;
    cfgKeys["F5"] = DIK_F5;
    cfgKeys["F6"] = DIK_F6;
    cfgKeys["F7"] = DIK_F7;
    cfgKeys["F8"] = DIK_F8;
    cfgKeys["F9"] = DIK_F9;
    cfgKeys["F10"] = DIK_F10;
    cfgKeys["F11"] = DIK_F11;
    cfgKeys["F12"] = DIK_F12;
    cfgKeys["F13"] = DIK_F13;
    cfgKeys["F14"] = DIK_F14;
    cfgKeys["F15"] = DIK_F15;
    cfgKeys["G"] = DIK_G;
    cfgKeys["GRAVE"] = DIK_GRAVE;
    cfgKeys["H"] = DIK_H;
    cfgKeys["HOME"] = DIK_HOME;
    cfgKeys["I"] = DIK_I;
    cfgKeys["INSERT"] = DIK_INSERT;
    cfgKeys["J"] = DIK_J;
    cfgKeys["K"] = DIK_K;
    cfgKeys["L"] = DIK_L;
    cfgKeys["LBRACKET"] = DIK_LBRACKET;
    cfgKeys["LCONTROL"] = DIK_LCONTROL;
    cfgKeys["LEFT"] = DIK_LEFT;
    cfgKeys["LALT"] = DIK_LMENU;
    cfgKeys["LSHIFT"] = DIK_LSHIFT;
    cfgKeys["M"] = DIK_M;
    cfgKeys["MINUS"] = DIK_MINUS;
    cfgKeys["NUMPADMUL"] = DIK_MULTIPLY;
    cfgKeys["N"] = DIK_N;
    cfgKeys["PAGEDOWN"] = DIK_NEXT;
    cfgKeys["NUMLOCK"] = DIK_NUMLOCK;
    cfgKeys["NUMPAD0"] = DIK_NUMPAD0;
    cfgKeys["NUMPAD1"] = DIK_NUMPAD1;
    cfgKeys["NUMPAD2"] = DIK_NUMPAD2;
    cfgKeys["NUMPAD3"] = DIK_NUMPAD3;
    cfgKeys["NUMPAD4"] = DIK_NUMPAD4;
    cfgKeys["NUMPAD5"] = DIK_NUMPAD5;
    cfgKeys["NUMPAD6"] = DIK_NUMPAD6;
    cfgKeys["NUMPAD7"] = DIK_NUMPAD7;
    cfgKeys["NUMPAD8"] = DIK_NUMPAD8;
    cfgKeys["NUMPAD9"] = DIK_NUMPAD9;
    cfgKeys["NUMPADENTER"] = DIK_NUMPADENTER;
    cfgKeys["O"] = DIK_O;
    cfgKeys["P"] = DIK_P;
    cfgKeys["PERIOD"] = DIK_PERIOD;
    cfgKeys["PAGEUP"] = DIK_PRIOR;
    cfgKeys["Q"] = DIK_Q;
    cfgKeys["R"] = DIK_R;
    cfgKeys["RBRACKET"] = DIK_RBRACKET;
    cfgKeys["RCONTROL"] = DIK_RCONTROL;
    cfgKeys["RETURN"] = DIK_RETURN;
    cfgKeys["RIGHT"] = DIK_RIGHT;
    cfgKeys["RALT"] = DIK_RMENU;
    cfgKeys["RSHIFT"] = DIK_RSHIFT;
    cfgKeys["S"] = DIK_S;
    cfgKeys["SEMICOLON"] = DIK_SEMICOLON;
    cfgKeys["SLASH"] = DIK_SLASH;
    cfgKeys["SPACE"] = DIK_SPACE;
    cfgKeys["NUMPADSUB"] = DIK_SUBTRACT;
    cfgKeys["T"] = DIK_T;
    cfgKeys["TAB"] = DIK_TAB;
    cfgKeys["U"] = DIK_U;
    cfgKeys["UP"] = DIK_UP;
    cfgKeys["V"] = DIK_V;
    cfgKeys["W"] = DIK_W;
    cfgKeys["X"] = DIK_X;
    cfgKeys["Y"] = DIK_Y;
    cfgKeys["Z"] = DIK_Z;
	cfgKeys["NONE"] = 0;

    kmap_.LeftTrigger			= cfgKeys[CIniFile::GetValueDef("LeftTrigger"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RightTrigger			= cfgKeys[CIniFile::GetValueDef("RightTrigger"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.Start					= cfgKeys[CIniFile::GetValueDef("Start"				,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.Back					= cfgKeys[CIniFile::GetValueDef("Back"				,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.LeftThumbClick		= cfgKeys[CIniFile::GetValueDef("LeftThumbClick"	,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RightThumbClick		= cfgKeys[CIniFile::GetValueDef("RightThumbClick"	,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.LeftShoulder			= cfgKeys[CIniFile::GetValueDef("LeftShoulder"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RightShoulder			= cfgKeys[CIniFile::GetValueDef("RightShoulder"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.A						= cfgKeys[CIniFile::GetValueDef("A"					,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.B						= cfgKeys[CIniFile::GetValueDef("B"					,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.X						= cfgKeys[CIniFile::GetValueDef("X"					,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.Y						= cfgKeys[CIniFile::GetValueDef("Y"					,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.LXLeft				= cfgKeys[CIniFile::GetValueDef("LeftXAxisLeft"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.LXRight				= cfgKeys[CIniFile::GetValueDef("LeftXAxisRight"	,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.LYUp					= cfgKeys[CIniFile::GetValueDef("LeftYAxisUp"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.LYDown				= cfgKeys[CIniFile::GetValueDef("LeftYAxisDown"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RXLeft				= cfgKeys[CIniFile::GetValueDef("RightXAxisLeft"	,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RXRight				= cfgKeys[CIniFile::GetValueDef("RightXAxisRight"	,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RYUp					= cfgKeys[CIniFile::GetValueDef("RightYAxisUp"		,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.RYDown				= cfgKeys[CIniFile::GetValueDef("RightYAxisDown"	,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.DPadUp				= cfgKeys[CIniFile::GetValueDef("DPadUp"			,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.DPadRight				= cfgKeys[CIniFile::GetValueDef("DPadRight"			,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.DPadDown				= cfgKeys[CIniFile::GetValueDef("DPadDown"			,GetDevName(),CONFIG_INI_NAME,"NONE")];
    kmap_.DPadLeft				= cfgKeys[CIniFile::GetValueDef("DPadLeft"			,GetDevName(),CONFIG_INI_NAME,"NONE")];
}

void VirtualKeyboard::Prepare() {
	if(!inited)
	{
		inited = true;
		if(FAILED(dev_->SetDataFormat(&c_dfDIKeyboard)))
			throw std::runtime_error("Got problem");

		if(FAILED(dev_->SetCooperativeLevel(GetTopWindow(HWND_DESKTOP), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
			throw std::runtime_error("Got problem");
	}
}

void VirtualKeyboard::Acq() {
	if(!inited)
		VirtualDirectInputDevice::Acq();
}

void VirtualKeyboard::Poll()
{
#define KEYDOWN(key) (keys[key] & 0x80)

	HRESULT hr;
	hr = dev_->GetDeviceState(sizeof(keys), &keys);
	if (FAILED(hr)) 
	{
		hr = dev_->Acquire();
		return;
	}

	memset(&state_.Gamepad,0,sizeof(XINPUT_GAMEPAD));
	if(kmap_.LeftTrigger)		state_.Gamepad.bLeftTrigger		= KEYDOWN(kmap_.LeftTrigger)?255:0;
	if(kmap_.RightTrigger)		state_.Gamepad.bRightTrigger	= KEYDOWN(kmap_.RightTrigger)?255:0;

	if(kmap_.LXLeft)			if(KEYDOWN(kmap_.LXLeft))	state_.Gamepad.sThumbLX		-= 32767;
	if(kmap_.LXRight)			if(KEYDOWN(kmap_.LXRight))	state_.Gamepad.sThumbLX		+= 32767;
	if(kmap_.LYUp)				if(KEYDOWN(kmap_.LYUp))		state_.Gamepad.sThumbLY		+= 32767;
	if(kmap_.LYDown)			if(KEYDOWN(kmap_.LYDown))	state_.Gamepad.sThumbLY		-= 32767;
	if(kmap_.RXLeft)			if(KEYDOWN(kmap_.RXLeft))	state_.Gamepad.sThumbRX		-= 32767;
    if(kmap_.RXRight)			if(KEYDOWN(kmap_.RXRight))	state_.Gamepad.sThumbRX		+= 32767;
    if(kmap_.RYUp)	 			if(KEYDOWN(kmap_.RYUp))		state_.Gamepad.sThumbRY		+= 32767;
    if(kmap_.RYDown) 			if(KEYDOWN(kmap_.RYDown))	state_.Gamepad.sThumbRY		-= 32767;

	if(kmap_.Start)				if(KEYDOWN(kmap_.Start))			state_.Gamepad.wButtons |= XINPUT_GAMEPAD_START;
    if(kmap_.Back)				if(KEYDOWN(kmap_.Back))				state_.Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;
    if(kmap_.LeftThumbClick)	if(KEYDOWN(kmap_.LeftThumbClick))	state_.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_THUMB;
    if(kmap_.RightThumbClick)	if(KEYDOWN(kmap_.RightThumbClick))	state_.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_THUMB;
    if(kmap_.LeftShoulder)		if(KEYDOWN(kmap_.LeftShoulder))		state_.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
    if(kmap_.RightShoulder)		if(KEYDOWN(kmap_.RightShoulder))	state_.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
    if(kmap_.A)					if(KEYDOWN(kmap_.A))				state_.Gamepad.wButtons |= XINPUT_GAMEPAD_A;
    if(kmap_.B)					if(KEYDOWN(kmap_.B))				state_.Gamepad.wButtons |= XINPUT_GAMEPAD_B;
    if(kmap_.X)					if(KEYDOWN(kmap_.X))				state_.Gamepad.wButtons |= XINPUT_GAMEPAD_X;
    if(kmap_.Y)					if(KEYDOWN(kmap_.Y))				state_.Gamepad.wButtons |= XINPUT_GAMEPAD_Y;

	if(kmap_.DPadUp)			if(KEYDOWN(kmap_.DPadUp))			state_.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	if(kmap_.DPadRight)			if(KEYDOWN(kmap_.DPadRight))		state_.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
    if(kmap_.DPadDown)			if(KEYDOWN(kmap_.DPadDown))			state_.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
    if(kmap_.DPadLeft)			if(KEYDOWN(kmap_.DPadLeft))			state_.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
}


VirtualKeyboard::~VirtualKeyboard(void)
{
	refCount--;
	if(refCount == 0) {
		UnAcq();
		dev_->Release();
	}
}

bool VirtualKeyboard::inited = false;
int VirtualKeyboard::refCount = 0;