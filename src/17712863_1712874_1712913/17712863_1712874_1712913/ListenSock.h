#ifndef CL_LISTENSOCK_H
#define CL_LISTENSOCK_H

#include "CSockThread.h"
//
// Handle Communication between Proxy and client
//


class CProxySock : public CSocket
{
public:
	CProxySock() : CSocket() {}
	virtual ~CProxySock() {}
	
	virtual void OnAccept(int nErrorCode);
private:
};
#endif