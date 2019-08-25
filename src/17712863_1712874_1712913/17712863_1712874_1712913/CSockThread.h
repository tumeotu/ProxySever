#ifndef CL_CSOCKTHREAD_H
#define CL_CSOCKTHREAD_H

#include "pch.h"
#include "RequestHandlerSock.h"
#include "MessagesID.h"

class CSockThread : public CWinThread
{
protected:
	DECLARE_DYNCREATE(CSockThread)
public:
	SOCKET m_hConnected;
	
	CSockThread() : CWinThread(), m_hConnected(0) {}
	virtual ~CSockThread() {}

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();

	int CacheData(const char* fileName, const char* buffer, int len, bool IsAppend = false);
	std::string ReFormatUri(const CStringA& str);
private:
	CRequestHandlerSock m_sConnected;
};

#endif