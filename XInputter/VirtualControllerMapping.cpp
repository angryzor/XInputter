#include "VirtualControllerMapping.h"

// Worthless constructors
Mapping::Mapping(bool invert, bool flip): invert_(invert), flip_(flip)
{}

AnalogMapping::AnalogMapping(AnalogInput* inp, bool invert, bool flip): inp_(inp), Mapping(invert,flip)
{}

HalfAnalogMapping::HalfAnalogMapping(AnalogInput* inp, bool invert, bool flip): AnalogMapping(inp,invert,flip)
{}

DigitalMapping::DigitalMapping(bool invert, bool flip): Mapping(invert,flip)
{}

POVMapping::POVMapping(BYTE idx, bool invert, bool flip, Position pos): idx_(idx-1), pos_(pos), DigitalMapping(invert,flip)
{}

ButtonMapping::ButtonMapping(BYTE idx, bool invert, bool flip): idx_(idx-1), DigitalMapping(invert,flip)
{}

Axis::Axis(BYTE idx): idx_(idx-1)
{}

Slider::Slider(BYTE idx): idx_(idx-1)
{}

// Mappings
BYTE Mapping::ReadAsTrigger(DIJOYSTATE2& js)
{
	return invert_?(255-AsTrigger(js)):AsTrigger(js);
}

SHORT Mapping::ReadAsAxis(DIJOYSTATE2& js)
{
	return invert_?(-AsAxis(js)):AsAxis(js);
}

bool Mapping::ReadAsButton(DIJOYSTATE2& js)
{
	return invert_?(!AsButton(js)):AsButton(js);
}

// Analog Mappings

SHORT AnalogMapping::AsAxis(DIJOYSTATE2 &js)
{
	return static_cast<SHORT>(AVal(js));
}

BYTE AnalogMapping::AsTrigger(DIJOYSTATE2 &js) 
{
	return static_cast<BYTE>((AVal(js) >> 8) + 128);
}

bool AnalogMapping::AsButton(DIJOYSTATE2 &js)
{
	return AVal(js) > 0;
}

long AnalogMapping::AVal(DIJOYSTATE2 &js)
{
	return flip_?(-inp_->AVal(js)):inp_->AVal(js);
}

// Digital Mappings

SHORT DigitalMapping::AsAxis(DIJOYSTATE2 &js)
{
	return (flip_?(!IsPressed(js)):IsPressed(js))?32767:0;
}

BYTE DigitalMapping::AsTrigger(DIJOYSTATE2 &js) 
{
	return (flip_?(!IsPressed(js)):IsPressed(js))?255:0;
}

bool DigitalMapping::AsButton(DIJOYSTATE2 &js)
{
	return flip_?(!IsPressed(js)):IsPressed(js);
}

// Analog Mapping Specifications: Rescalers:
long HalfAnalogMapping::AVal(DIJOYSTATE2 &js)
{
	long v = AnalogMapping::AVal(js) * 2;
	return (v > 0)?(v - 32767):-32767;
}

// Digital Mapping Specifications: IsPressed routine
bool ButtonMapping::IsPressed(DIJOYSTATE2 &js)
{
	bool res = js.rgbButtons[idx_] & 0x80;
	return res;
}

bool POVMapping::IsPressed(DIJOYSTATE2 &js)
{
	unsigned long x(js.rgdwPOV[idx_]);
	if(LOWORD(x) == 0xFFFF) 
		return false;
	switch(pos_) {
		case UP:
			return 31500 <= x || x <= 4500;
		case RIGHT:
			return 4500 <= x && x <= 13500;
		case DOWN:
			return 13500 <= x && x <= 22500;
		case LEFT:
		default:
			return 22500 <= x && x <= 31500;
	}
}

// Analog Inputs
long Axis::AVal(DIJOYSTATE2 &js)
{
	switch(idx_) {
		case 0:
			return js.lX;
		case 1:
			return js.lY;
		case 2:
			return js.lZ;
		case 3:
			return js.lRx;
		case 4:
			return js.lRy;
		case 5:
		default:
			return js.lRz;
	}
}

long Slider::AVal(DIJOYSTATE2 &js)
{
	return js.rglSlider[idx_];
}
