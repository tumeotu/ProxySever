
// Server.h : main header file for the PROJECT_NAME application
//

#ifndef CL_SERVER_H
#define CL_SERVER_H

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "ServerDlg.h"
#include "pch.h"
// CServerApp:
// See Server.cpp for the implementation of this class
//

class CServerApp : public CWinApp
{
public:
	CServerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	void Log(const CString&);
	void Log(const CStringA& msg) { this->Log(CString(msg)); }
	const static UINT m_WM_BRINGFRONT;

private:
	std::mutex SockThreadLocker;
	std::mutex LoggingLocker;

	HANDLE m_Mutex_h;

};

//Global objects

extern const std::string FILE_BLACKLIST;
extern const std::string FOLDER_CACHE;
extern const int CACHE_MAX_AGE;
extern std::vector<CStringA> vBlackList;
extern CServerApp theApp;

#endif