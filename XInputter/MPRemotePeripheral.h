#pragma once
#include <winsock2.h>
#include "virtualperipheral.h"
#include <boost/thread.hpp>

class MPRemotePeripheral :
	public VirtualPeripheral
{
	friend class MPRemotePeripheralReceiver;

public:
	MPRemotePeripheral(void);
	virtual ~MPRemotePeripheral(void);

	virtual DWORD GetState(XINPUT_STATE* pState);

private:
	MPRemotePeripheral(MPRemotePeripheral&);
	MPRemotePeripheral& operator=(MPRemotePeripheral&);

private:
	SOCKET sock_;
	WSADATA wsaData_;
	CRITICAL_SECTION cs_;
	boost::thread* t_;
};

class MPRemotePeripheralReceiver {
public:
	MPRemotePeripheralReceiver(MPRemotePeripheral& mprp);
	void operator()();
private:
	MPRemotePeripheral& mprp_;
};