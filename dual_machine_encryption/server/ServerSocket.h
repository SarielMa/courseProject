#if !defined(AFX_SERVERSOCKET_H__DE6D3190_0196_4281_80D4_AC490BA0B05A__INCLUDED_)
#define AFX_SERVERSOCKET_H__DE6D3190_0196_4281_80D4_AC490BA0B05A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();
	void CServerSocket::OnReceive(int nErrorCode)
	{    
		AfxMessageBox("OnReceive");
		CString strTmp("");
		strTmp.GetBuffer(1000);
		m_WorkSocket.Receive((void*)(strTmp.GetBuffer(0)),10);
		m_RcvQueue.push(strTmp);
		AfxMessageBox(strTmp);
		CSocket::OnReceive(nErrorCode);
	}


// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__DE6D3190_0196_4281_80D4_AC490BA0B05A__INCLUDED_)
