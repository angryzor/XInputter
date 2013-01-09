#pragma once
#include <windows.h>
#include <XInput.h>
#include <string>

class VirtualPeripheral
{
public:
	VirtualPeripheral(const std::string& devName);
	const std::string& GetDevName() const;

	virtual DWORD GetState(XINPUT_STATE* pState);
	virtual DWORD SetState(XINPUT_VIBRATION* pVibration);
	virtual DWORD GetCaps(DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities);
	virtual void Enable(BOOL enable);

	virtual ~VirtualPeripheral(void);
protected:
	static std::string MakeDevName(const std::string& name, int idx);
private:
	void ResetData();

private:
	VirtualPeripheral(VirtualPeripheral&);
	VirtualPeripheral& operator=(VirtualPeripheral&);

protected:
	XINPUT_STATE state_;
	XINPUT_CAPABILITIES caps_;
private:
	std::string devName_;
};
