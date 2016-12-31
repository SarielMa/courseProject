; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServerSocket
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "服务器1_1.h"

ClassCount=4
Class1=CMy1_1App
Class2=CMy1_1Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CServerSocket
Resource3=IDD_MY1_1_DIALOG

[CLS:CMy1_1App]
Type=0
HeaderFile=服务器1_1.h
ImplementationFile=服务器1_1.cpp
Filter=N

[CLS:CMy1_1Dlg]
Type=0
HeaderFile=服务器1_1Dlg.h
ImplementationFile=服务器1_1Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_data

[CLS:CAboutDlg]
Type=0
HeaderFile=服务器1_1Dlg.h
ImplementationFile=服务器1_1Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY1_1_DIALOG]
Type=1
Class=CMy1_1Dlg
ControlCount=5
Control1=IDC_LIST,SysListView32,1350631425
Control2=IDC_start,button,1342242816
Control3=IDC_data,button,1342242816
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CServerSocket]
Type=0
HeaderFile=ServerSocket.h
ImplementationFile=ServerSocket.cpp
BaseClass=CSocket
Filter=N

