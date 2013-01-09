#pragma once
#include "virtualperipheral.h"

class VirtualX360Controller :
	public VirtualPeripheral
{
public:
	VirtualX360Controller(int joyIdx);
	virtual DWORD GetState(XINPUT_STATE* pState);
	virtual DWORD SetState(XINPUT_VIBRATION* pVibration);
	virtual DWORD GetCaps(DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities);
	virtual void Enable(BOOL enable);
	virtual ~VirtualX360Controller(void);
protected:
	typedef DWORD	(WINAPI *XIGS)(DWORD,XINPUT_STATE*);
	typedef DWORD	(WINAPI *XISS)(DWORD,XINPUT_VIBRATION*);
	typedef DWORD	(WINAPI *XIGC)(DWORD,DWORD,XINPUT_CAPABILITIES*);
	typedef void	(WINAPI *XIE )(BOOL);

	unsigned int channel_;
	static int refCount;
	static HMODULE realxinput_;
	static XIGS xigs_;
	static XISS xiss_;
	static XIGC xigc_;
	static XIE	xie_;
};
