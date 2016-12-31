// Result.cpp : 实现文件
//

#include "stdafx.h"
#include "WinpcapMFC.h"
#include "Result.h"
#include "afxdialogex.h"


// CResult 对话框

IMPLEMENT_DYNAMIC(CResult, CDialogEx)

CResult::CResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResult::IDD, pParent)
	, DBName(_T(""))
{

}

CResult::~CResult()
{
}

void CResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST_RESULT, resultListControl);
	//DDX_Control(pDX, IDC_LIST1, listResult);
	DDX_Text(pDX, IDC_EDIT_DBNAME, DBName);
	DDX_Control(pDX, IDC_LIST_RESULT, listControlResult);
}


BEGIN_MESSAGE_MAP(CResult, CDialogEx)
	ON_BN_CLICKED(IDOK, &CResult::OnBnClickedOk)
END_MESSAGE_MAP()


// CResult 消息处理程序

void CResult::SetCtrlStyle(HWND hWnd, DWORD dwNewStyle)
{
	DWORD dwOldStyle;
	dwOldStyle = GetWindowLong(hWnd, GWL_STYLE);
	if ((dwOldStyle&LVS_TYPEMASK) != dwNewStyle)
	{
		dwOldStyle &= ~LVS_TYPEMASK;
		dwNewStyle |= dwOldStyle;
		SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
	}
}


char* CStrToChar(CString strSrc)
{
    #ifdef UNICODE
        DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, NULL, 0, NULL, FALSE);
        char *psText;
        psText = new char[dwNum];
        if (!psText)
            delete []psText;
        WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, psText, dwNum, NULL, FALSE);
        return (char*)psText;
    #else
        return (LPCTSRT)strSrc;
    #endif
}


void CResult::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//SetCtrlStyle(resultListControl.m_hWnd,LVS_REPORT);
	UpdateData(true);
	listControlResult.DeleteAllItems();
	SetCtrlStyle(listControlResult.m_hWnd,LVS_REPORT);
	CString strHeader[2]={ _T("类型"), _T("数量")};
	int nWidth[2] = {200, 200};
	for (int nCol=0; nCol<2; nCol++)
		listControlResult.InsertColumn(nCol,strHeader[nCol],LVCFMT_LEFT,nWidth[nCol]);

	fillResult(CStrToChar(DBName));
}

const char* queryString(char * name,char * db,char * layer,char * kind)
{
	char  temp[100];
	sprintf(temp,"SELECT COUNT(*) AS %s FROM %s WHERE %s=\'%s\';",name,db,layer,kind);
	const char * result=temp;
	
	return result;
}


int CResult::queryFill(MYSQL *sock,char *queryString)
{
		if(mysql_real_query(sock,queryString,(UINT)strlen(queryString))!=0)
		{ 
			MessageBox(_T("数据库中表格出错")); 
			return -1;
		}

		MYSQL_RES *result;
		MYSQL_ROW row;
		if(!(result=mysql_use_result(sock)))
		{ 
			MessageBox(_T("读取数据集失败"));
			return -1;
		}

		if(row=mysql_fetch_row(result))
		{
			CString str1( result->fields->name);
			int index=listControlResult.InsertItem(listControlResult.GetItemCount(),str1);
		
			CString str2(row[0]);
			listControlResult.SetItemText(index,1,str2);

		}
		mysql_free_result(result);

		return 0;
}

void CResult::fillResult(char * intoDB)
{
	char *host = "localhost"; 
    char *user = "root"; 
    char *pass = "123456";//你的mysql服务器密码 
    char *db = "testdb"; //使用的数据库
    unsigned int port = 3306; //server port  
	MYSQL *sock; 
    MYSQL_RES *res; 
    MYSQL_FIELD * fd; 
    MYSQL_ROW row; 
    char buffer1[500]=""; 
	int i; 

	sock=mysql_init(0);

    if(sock && mysql_real_connect(sock,host,user,pass,db,0,NULL,0)) 
    { //连接数据库
        //printf("connect mysql succeed!\n");

        mysql_query(sock, "set names gb2312"); 

		char ch_query[100];

		sprintf(ch_query,"SELECT COUNT(*) AS SUM FROM %s",intoDB);

		if(queryFill(sock,ch_query)==-1)
		{
			return;
		}

		char kind[10][10]={"IP","ARP","ICMP","TCP","UDP","HTTP","SMTP","FTP","DHCP"};
		char layer[10][20]={"network_layer","network_layer","network_layer",
			"transport_layer","transport_layer",
			"app_layer","app_layer","app_layer","app_layer"};
		
		for ( int count=0;count<9;count++ )
		{
			strcpy(ch_query,queryString(kind[count],intoDB,layer[count],kind[count]));	
			if(queryFill(sock,ch_query)==-1)
				return;
		}

	}
    mysql_close(sock);//断开连接 
	MessageBox(_T("查询成功"));
}