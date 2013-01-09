#include "StdAfx.h"
#include "VirtualController.h"
#include <sstream>
#include <fstream>
#include "IniFile.h"

BOOL CALLBACK EnumAxesCallback(
         LPCDIDEVICEOBJECTINSTANCE pdidoi,
         LPVOID pvRef
)
{
	VirtualController* vc = (VirtualController*)pvRef;

	DIPROPRANGE diprg; 

	diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	diprg.diph.dwHow        = DIPH_BYID; 
	diprg.diph.dwObj        = pdidoi->dwType; 
	diprg.lMin              = -32767; 
	diprg.lMax              = +32767; 

	if(FAILED(vc->dev_->SetProperty(DIPROP_RANGE, &diprg.diph)))
		return DIENUM_STOP;
	return DIENUM_CONTINUE;
}

VirtualController::VirtualController(LPDIRECTINPUTDEVICE8 dev, int joyIdx): VirtualDirectInputDevice(MakeDevName("Joy",joyIdx),dev)
{
	ResetData();
}

Mapping* VirtualController::MakeMapping(std::string cfg, std::string defopt, std::string def) {
	bool invert = false;
	bool flip = false;
	unsigned int idx;

	std::string::size_type n(cfg.find_first_of("0123456789"));
	if(n == std::string::npos)
		return MakeMapping(def,"","");

	istringstream iss(cfg.substr(n));
	if(!(iss >> idx))
		return MakeMapping(def,"","");

	if(cfg.find("-") != std::string::npos)
		invert = true;
	if(cfg.find("!") != std::string::npos)
		flip = true;
	if(cfg.find("ha") != std::string::npos)
		return new HalfAnalogMapping(new Axis((BYTE)idx), invert, flip);
	if(cfg.find("hs") != std::string::npos)
		return new HalfAnalogMapping(new Slider((BYTE)idx), invert, flip);
	if(cfg.find("a") != std::string::npos)
		return new AnalogMapping(new Axis((BYTE)idx), invert, flip);
	if(cfg.find("s") != std::string::npos)
		return new AnalogMapping(new Slider((BYTE)idx), invert, flip);
	if(cfg.find("b") != std::string::npos)
		return new ButtonMapping((BYTE)idx, invert, flip);
	if(cfg.find("p") != std::string::npos) {
		if(cfg.find("u") != std::string::npos)
			return new POVMapping((BYTE)idx, invert, flip, POVMapping::UP);
		if(cfg.find("r") != std::string::npos)
			return new POVMapping((BYTE)idx, invert, flip, POVMapping::RIGHT);
		if(cfg.find("d") != std::string::npos)
			return new POVMapping((BYTE)idx, invert, flip, POVMapping::DOWN);
		if(cfg.find("l") != std::string::npos)
			return new POVMapping((BYTE)idx, invert, flip, POVMapping::LEFT);
		throw std::runtime_error("Unknown DPad direction");
	}
	if(defopt == "") {
		if(def == "") throw std::runtime_error("Input problem");
		else return MakeMapping(def,"",""); // I find this ugly :p
	}
	else return MakeMapping(cfg+defopt,"",def);
}

Mapping* VirtualController::LoadMapping(std::string name, std::string defopt, std::string def) {
	return MakeMapping(CIniFile::GetValue(name,GetDevName(),CONFIG_INI_NAME),defopt,def);
}
	
void VirtualController::ResetData() {
	map_.LeftTrigger		= LoadMapping("LeftTrigger","b","b7");
	map_.RightTrigger		= LoadMapping("RightTrigger","b","b8");
	map_.Start				= LoadMapping("Start","b","b10");
	map_.Back				= LoadMapping("Back","b","b9");
	map_.LeftThumbClick		= LoadMapping("LeftThumbClick","b","b11");
	map_.RightThumbClick	= LoadMapping("RightThumbClick","b","b12");
	map_.LeftShoulder		= LoadMapping("LeftShoulder","b","b5");
	map_.RightShoulder		= LoadMapping("RightShoulder","b","b6");
	map_.A					= LoadMapping("A","b","b1");
	map_.B					= LoadMapping("B","b","b2");
	map_.X					= LoadMapping("X","b","b3");
	map_.Y					= LoadMapping("Y","b","b4");

	map_.LX					= LoadMapping("LeftXAxis","a","a1");
	map_.LY					= LoadMapping("LeftYAxis","a","-a2");
	map_.RX					= LoadMapping("RightXAxis","a","a3");
	map_.RY					= LoadMapping("RightYAxis","a","-a6");

	map_.DPadLeft			= LoadMapping("DPadLeft","pl","pl1");
	map_.DPadUp				= LoadMapping("DPadUp","pu","pu1");
	map_.DPadRight			= LoadMapping("DPadRight","pr","pr1");
	map_.DPadDown			= LoadMapping("DPadDown","pd","pd1");
}

void VirtualController::Poll() {
	HRESULT hr;
	hr = dev_->Poll(); 
	if (FAILED(hr)) 
	{
		hr = dev_->Acquire();
		if(hr == DIERR_INPUTLOST) // Don't lose time here, we'll get it in the next pass
			return;
	}
	DIJOYSTATE2 js;
	dev_->GetDeviceState(sizeof(DIJOYSTATE2), &js);

	state_.Gamepad.sThumbLX = map_.LX->ReadAsAxis(js);
	state_.Gamepad.sThumbLY = map_.LY->ReadAsAxis(js);
	state_.Gamepad.sThumbRX = map_.RX->ReadAsAxis(js);
	state_.Gamepad.sThumbRY = map_.RY->ReadAsAxis(js);

	state_.Gamepad.bLeftTrigger = map_.LeftTrigger->ReadAsTrigger(js);
	state_.Gamepad.bRightTrigger = map_.RightTrigger->ReadAsTrigger(js);

	WORD buts = 0;
	if(map_.Start->ReadAsButton(js)				) buts |= XINPUT_GAMEPAD_START;
	if(map_.Back->ReadAsButton(js)				) buts |= XINPUT_GAMEPAD_BACK;
	if(map_.LeftThumbClick->ReadAsButton(js)	) buts |= XINPUT_GAMEPAD_LEFT_THUMB;
	if(map_.RightThumbClick->ReadAsButton(js)	) buts |= XINPUT_GAMEPAD_RIGHT_THUMB;
	if(map_.LeftShoulder->ReadAsButton(js)		) buts |= XINPUT_GAMEPAD_LEFT_SHOULDER;
	if(map_.RightShoulder->ReadAsButton(js)		) buts |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
	if(map_.A->ReadAsButton(js)					) buts |= XINPUT_GAMEPAD_A;
	if(map_.B->ReadAsButton(js)					) buts |= XINPUT_GAMEPAD_B;
	if(map_.X->ReadAsButton(js)					) buts |= XINPUT_GAMEPAD_X;
	if(map_.Y->ReadAsButton(js)					) buts |= XINPUT_GAMEPAD_Y;
	if(map_.DPadUp->ReadAsButton(js)			) buts |= XINPUT_GAMEPAD_DPAD_UP;
	if(map_.DPadRight->ReadAsButton(js)			) buts |= XINPUT_GAMEPAD_DPAD_RIGHT;
	if(map_.DPadDown->ReadAsButton(js)			) buts |= XINPUT_GAMEPAD_DPAD_DOWN;
	if(map_.DPadLeft->ReadAsButton(js)			) buts |= XINPUT_GAMEPAD_DPAD_LEFT;

	state_.Gamepad.wButtons = buts;
	
	state_.dwPacketNumber++;
}

void VirtualController::Prepare()
{
	HRESULT hr;
	if (FAILED(hr = dev_->SetDataFormat(&c_dfDIJoystick2)))
		throw std::runtime_error("Got problem");

	if (FAILED(hr = dev_->EnumObjects(EnumAxesCallback, 
                                       (VOID*)this, DIDFT_AXIS)))
		throw std::runtime_error("Got problem");

	if (FAILED(hr = dev_->SetCooperativeLevel(GetTopWindow(HWND_DESKTOP), 
                    DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		return;
}

VirtualController::~VirtualController(void)
{
	UnAcq();
	dev_->Release();

	delete map_.LeftTrigger;
	delete map_.RightTrigger;
	delete map_.Start;
	delete map_.Back;
	delete map_.LeftThumbClick;
	delete map_.RightThumbClick;
	delete map_.LeftShoulder;
	delete map_.RightShoulder;
	delete map_.A;
	delete map_.B;
	delete map_.X;
	delete map_.Y;
	delete map_.LX;
	delete map_.LY;
	delete map_.RX;
	delete map_.RY;
	delete map_.DPadLeft;
	delete map_.DPadUp;
	delete map_.DPadRight;
	delete map_.DPadDown;
}
	

