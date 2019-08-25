
// ServerDlg.h : header file
//

#ifndef CL_SERVERDLG_H
#define CL_SERVERDLG_H

#include "ListenSock.h"

// CServerDlg dialog
class CServerDlg : public CDialogEx
{
// Construction
public:
	CServerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CProxySock m_sListen;	// Handle communication between client and proxy server
	CString m_LoggingTextCtrl;

public:
	const UINT PORT = 8888u;
	const UINT MAXPENDING = 3u;

	void Logging(CString);
	void ClearLog();

	afx_msg void OnBnClickedClearLog() { ClearLog(); }
	afx_msg void OnClose();
};

#endif