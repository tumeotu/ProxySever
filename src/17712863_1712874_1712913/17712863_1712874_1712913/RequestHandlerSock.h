#pragma once

#include <afxsock.h>
#include "pch.h"
class CRequestHandlerSock : public CSocket
{
public:

	CRequestHandlerSock() : CSocket(),strPortCache(_T("")) {}
	virtual ~CRequestHandlerSock() {}

	static HttpHeader CRequestHandlerSock::RequestParser(const CStringA& rqst);
private:
	CStringA strPortCache;
};

