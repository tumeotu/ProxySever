
// ServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
	, m_LoggingTextCtrl(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	if (AfxSocketInit() == FALSE)
	{
		AfxMessageBox(L"Unable to init socket library", MB_ICONWARNING);
	}
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGGINGBOX, m_LoggingTextCtrl);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEARLOG, &CServerDlg::OnBnClickedClearLog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//Create cache folder
	_mkdir(FOLDER_CACHE.c_str());

	// Create proxy server
	Logging(L"Starting server...");
	if (m_sListen.Create(PORT, SOCK_STREAM) && m_sListen.Listen(MAXPENDING))
	{
		// Load list of Forbidden domains
		Logging(L"Finding " + CString(FILE_BLACKLIST.c_str(), FILE_BLACKLIST.length()) + L"...");
		std::ifstream readStream(FILE_BLACKLIST);
		if (readStream.is_open())
		{
			Logging(L"Initializing list of forbidden domains...");
			std::string temp;
			while (readStream.good())
			{
				std::getline(readStream, temp);
				if (temp == "") continue;
				CStringA foundDomain = CStringA(temp.c_str(), temp.length());
				vBlackList.push_back(foundDomain);
				Logging(CString("Found " + foundDomain));
			}

			if (!readStream.eof())
			{
				Logging(L"File is corrupted and need to be recreated! Previous found domains are preserved");
				std::ofstream writeStream(FILE_BLACKLIST);
				writeStream.close();
			}
			else
			{
				Logging(L"Finish initializing");
			}
		}
		else
		{
			Logging(L"File not found!");
		}

		Logging(L"Starting successfully! Server is running now...");
	}
	else
	{
		AfxMessageBox(L"Cannot open server with code: " + GetLastError(), MB_ICONERROR);
		::PostQuitMessage(0);
	}



	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerDlg::Logging(CString msg)
{
	if (msg == "") return;

	m_LoggingTextCtrl += msg + L"\r\n";

	//true means Control = > Data
	//false means Data = > Control
	SetDlgItemTextW(IDC_LOGGINGBOX, m_LoggingTextCtrl.GetString());
	//UpdateData(false);

}
void CServerDlg::ClearLog()
{
	m_LoggingTextCtrl = "";

	SetDlgItemTextW(IDC_LOGGINGBOX, m_LoggingTextCtrl.GetString());
}


void CServerDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_sListen.Close();
	CDialogEx::OnClose();
}
