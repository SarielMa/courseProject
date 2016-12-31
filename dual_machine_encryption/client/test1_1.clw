; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTest1_1Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "test1_1.h"

ClassCount=7
Class1=CTest1_1App
Class2=CTest1_1Dlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_algorithm
Resource2=IDR_MAINFRAME
Resource3=IDD_page1
Resource4=IDD_page2
Class4=Cpage1
Class5=Cpage2
Resource5=IDD_TEST1_1_DIALOG
Class6=Cselect
Resource6=IDD_ABOUTBOX
Class7=CkeyInput
Resource7=IDD_keyinput

[CLS:CTest1_1App]
Type=0
HeaderFile=test1_1.h
ImplementationFile=test1_1.cpp
Filter=N

[CLS:CTest1_1Dlg]
Type=0
HeaderFile=test1_1Dlg.h
ImplementationFile=test1_1Dlg.cpp
Filter=D
LastObject=IDC_IPADDRESS1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=test1_1Dlg.h
ImplementationFile=test1_1Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_CHECK1,button,1342242819

[DLG:IDD_TEST1_1_DIALOG]
Type=1
Class=CTest1_1Dlg
ControlCount=12
Control1=IDC_TAB1,SysTabControl32,1342177280
Control2=IDC_select,button,1342242816
Control3=IDC_send,button,1342242816
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_start,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_link,button,1342242816
Control11=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_page1]
Type=1
Class=Cpage1
ControlCount=6
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RADIO1,button,1342308361
Control6=IDC_RADIO2,button,1342177289

[DLG:IDD_page2]
Type=1
Class=Cpage2
ControlCount=8
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_browse1,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_open_C,static,1342308352
Control6=IDC_browse2,button,1342242816
Control7=IDC_RADIO1,button,1342308361
Control8=IDC_RADIO2,button,1342177289

[CLS:Cpage1]
Type=0
HeaderFile=page1.h
ImplementationFile=page1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT2

[CLS:Cpage2]
Type=0
HeaderFile=page2.h
ImplementationFile=page2.cpp
BaseClass=CDialog
Filter=D
LastObject=Cpage2
VirtualFilter=dWC

[DLG:IDD_algorithm]
Type=1
Class=Cselect
ControlCount=13
Control1=IDC_RADIO1,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_RADIO4,button,1342177289
Control5=IDC_RADIO5,button,1342177289
Control6=IDC_RADIO6,button,1342177289
Control7=IDC_RADIO7,button,1342177289
Control8=IDC_RADIO8,button,1342177289
Control9=IDC_RADIO9,button,1342177289
Control10=IDC_RADIO10,button,1342177289
Control11=IDC_choose,button,1342242816
Control12=IDC_RADIO11,button,1342177289
Control13=IDC_RADIO12,button,1342177289

[CLS:Cselect]
Type=0
HeaderFile=select.h
ImplementationFile=select.cpp
BaseClass=CDialog
Filter=D
LastObject=Cselect
VirtualFilter=dWC

[DLG:IDD_keyinput]
Type=1
Class=CkeyInput
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_EDIT9,edit,1350631552
Control12=IDC_EDIT10,edit,1350631552
Control13=IDC_EDIT_num,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_ENTER,button,1342242816

[CLS:CkeyInput]
Type=0
HeaderFile=keyInput.h
ImplementationFile=keyInput.cpp
BaseClass=CDialog
Filter=D
LastObject=CkeyInput
VirtualFilter=dWC

