#include "pch.h"
#include "RequestHandlerSock.h"
#include "Server.h"

HttpHeader CRequestHandlerSock::RequestParser(const CStringA& rqst)
{
	if (rqst == "") std::_Xinvalid_argument("CRequestHandlerSock::RequestParser => rqst");

	HttpHeader output;

	CStringA method, http, uri, hostName, strPort;

	size_t i = 0;
	// Get request's method
	for (i = 0;; i++)
	{
		if (rqst[i] == ' ') break;
		method.AppendChar(rqst[i]);
	}
	output.Method = method;

	// Get request's uri after method
	for (++i;; i++)
	{
		if (rqst[i] == 'H') break;
		uri.AppendChar(rqst[i]);
	}
	output.Uri = uri;

	// Get http version
	i = rqst.Find("HTTP");
	if (i >= 0)
	{
		for (i;; i++)
		{
			if (rqst[i] == '\r' || rqst[i] == '\n') break;
			http.AppendChar(rqst[i]);
		}
	}
	output.HttpVer = http;

	//Get host name and its port
	i = rqst.Find("Host");
	if (i >= 0)
	{
		i += 6; // offset to first character of host name, e.g: Host: mysite.com
		for (i; ; i++)
		{
			if (rqst[i] == ':' || rqst[i] == '\r' || rqst[i] == '\n') break;
			hostName.AppendChar(rqst[i]);
		}
		output.Host = hostName;

		if (rqst[i] == ':')
		{
			// Get port which follows hostname after a ':'
			for (++i;; i++)
			{
				if (rqst[i] == '\n' || rqst[i] == '\r') break;
				strPort.AppendChar(rqst[i]);
			}
			output.Port = strPort;
		}
	}

	CStringA logging = "";
	logging.Format("Method: %s\r\nURI: %s\r\nVersion: %s\r\nHost: %s\r\nPort: %s\r\n\r\n",
		output.Method,
		output.Uri,
		output.HttpVer,
		output.Host,
		output.Port
	);
	((CServerApp*) ::AfxGetApp())->Log(logging);

	return output;
}