#pragma once
#include <string>
#include "VirtualDirectInputDevice.h"
#include "VirtualControllerMapping.h"

struct Map {
	Mapping* LeftTrigger;
	Mapping* RightTrigger;
	Mapping* Start;
	Mapping* Back;
	Mapping* LeftThumbClick;
	Mapping* RightThumbClick;
	Mapping* LeftShoulder;
	Mapping* RightShoulder;
	Mapping* A;
	Mapping* B;
	Mapping* X;
	Mapping* Y;
	Mapping* LX;
	Mapping* LY;
	Mapping* RX;
	Mapping* RY;
	Mapping* DPadLeft;
	Mapping* DPadUp;
	Mapping* DPadRight;
	Mapping* DPadDown;
};

class VirtualController : public VirtualDirectInputDevice
{
	friend BOOL CALLBACK EnumAxesCallback(
         LPCDIDEVICEOBJECTINSTANCE lpddoi,
         LPVOID pvRef);
public:
	VirtualController(LPDIRECTINPUTDEVICE8 dev, int joyIdx);
	virtual ~VirtualController(void);

protected:
	virtual void Poll();
	virtual void Prepare();
private:
	void ResetData();
	Mapping* MakeMapping(std::string cfg, std::string defopt, std::string def);
	Mapping* LoadMapping(std::string name, std::string defopt, std::string def);

private:
	VirtualController(VirtualController&);
	VirtualController& operator=(VirtualController&);

private:
	Map map_;
};
