
// WinpcapMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWinpcapMFCApp:
// �йش����ʵ�֣������ WinpcapMFC.cpp
//

class CWinpcapMFCApp : public CWinApp
{
public:
	CWinpcapMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWinpcapMFCApp theApp;