#pragma once
#include <dinput.h>
#include "virtualperipheral.h"

class VirtualDirectInputDevice :
	public VirtualPeripheral
{
public:
	VirtualDirectInputDevice(const std::string& devName, LPDIRECTINPUTDEVICE8 dev);
	virtual ~VirtualDirectInputDevice(void);

	virtual DWORD GetState(XINPUT_STATE* pState);
	virtual void Enable(BOOL enable);
protected:
	virtual void Poll()=0;
	virtual void Prepare()=0;
	virtual void Acq();
	virtual void UnAcq();

private:
	VirtualDirectInputDevice(VirtualDirectInputDevice&);
	VirtualDirectInputDevice& operator=(VirtualDirectInputDevice&);

protected:
	LPDIRECTINPUTDEVICE8 dev_;
};
