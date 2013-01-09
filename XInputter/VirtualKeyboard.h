#pragma once
#include "VirtualDirectInputDevice.h"
#include <map>

struct KeyMap {
	BYTE LeftTrigger;
	BYTE RightTrigger;
	BYTE Start;
	BYTE Back;
	BYTE LeftThumbClick;
	BYTE RightThumbClick;
	BYTE LeftShoulder;
	BYTE RightShoulder;
	BYTE A;
	BYTE B;
	BYTE X;
	BYTE Y;
	BYTE LXLeft;
	BYTE LXRight;
	BYTE LYUp;
	BYTE LYDown;
	BYTE RXLeft;
	BYTE RXRight;
	BYTE RYUp;
	BYTE RYDown;
	BYTE DPadUp;
	BYTE DPadRight;
	BYTE DPadDown;
	BYTE DPadLeft;
};

class VirtualKeyboard : public VirtualDirectInputDevice
{
public:
	VirtualKeyboard(LPDIRECTINPUTDEVICE8 dev, int idx);
	virtual void Poll();
	virtual void Prepare();
	virtual void Acq();
	virtual ~VirtualKeyboard(void);

private:
	VirtualKeyboard(VirtualKeyboard&);
	VirtualKeyboard& operator=(VirtualKeyboard&);

private:
	static bool inited;
	BYTE keys[256];
	KeyMap kmap_;
	static int refCount;
};
