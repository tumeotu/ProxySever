#include "pch.h"
#include "ListenSock.h"
#include "Server.h"

void CProxySock::OnAccept(int nErrorCode)
{
	if (nErrorCode != 0) return CSocket::OnAccept(nErrorCode);

	CProxySock temp;

	if (Accept(temp) == FALSE)
	{
		CString msg = _T("");
		msg.Format(L"Cannot accept with error code: %i", GetLastError());
		AfxMessageBox(msg);
		return;
	}

	CString addr = _T("");
	UINT port = 0;
	temp.GetPeerName(addr, port);

	CSockThread* thread = (CSockThread*)AfxBeginThread(RUNTIME_CLASS(CSockThread), 0, 0u, CREATE_SUSPENDED);
	thread->m_hConnected = temp.Detach();
	thread->ResumeThread();

}
