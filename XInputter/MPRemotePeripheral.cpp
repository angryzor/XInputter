#include "MPRemotePeripheral.h"

MPRemotePeripheral::MPRemotePeripheral(void) : VirtualPeripheral(devName)
{
	WSAStartup(MAKEWORD(2,2), &wsaData_);

	sockaddr_in addr;

	sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(31000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sock_, (sockaddr*)&addr, sizeof(addr));

	DWORD timeout(85);
	setsockopt(sock_,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(DWORD));

	InitializeCriticalSection(&cs_);

	MPRemotePeripheralReceiver r(*this);
	t_ = new boost::thread(r);
}

DWORD MPRemotePeripheral::GetState(XINPUT_STATE* pState) {
	EnterCriticalSection(&cs_);
	DWORD res = VirtualPeripheral::GetState(pState);
	LeaveCriticalSection(&cs_);
	return res;
}

MPRemotePeripheral::~MPRemotePeripheral(void)
{
	t_->interrupt();
	t_->join();
	delete t_;

	DeleteCriticalSection(&cs_);

	closesocket(sock_);

	WSACleanup();
}

MPRemotePeripheralReceiver::MPRemotePeripheralReceiver(MPRemotePeripheral& mprp) : mprp_(mprp)
{
}

void MPRemotePeripheralReceiver::operator()() {
	sockaddr_in sender;
	int senderlen;
	char buf[sizeof(mprp_.state_)];

	try
	{
		while(true) {
			if(recvfrom(mprp_.sock_, buf, sizeof(mprp_.state_), 0, (sockaddr*)&sender, &senderlen) == SOCKET_ERROR)
				throw std::runtime_error("Receiving error");

			EnterCriticalSection(&mprp_.cs_);
			memcpy(&mprp_.state_, buf, sizeof(mprp_.state_));
			LeaveCriticalSection(&mprp_.cs_);
		}
	}
	catch(boost::thread_interrupted&)
	{
	}
	catch(std::runtime_error&)
	{
	}
}