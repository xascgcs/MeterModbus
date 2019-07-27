
// MeterModbusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MeterModbus.h"
#include "MeterModbusDlg.h"
#include "afxdialogex.h"
#include "NewCrc.h"
#include "FindFile.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMeterModbusDlg 对话框

CMeterModbusDlg::CMeterModbusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeterModbusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeterModbusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//
	DDX_Control(pDX, IDC_STATIC_ReadVal0, m_ReadVal[0]);
	DDX_Control(pDX, IDC_STATIC_ReadVal1, m_ReadVal[1]);
	DDX_Control(pDX, IDC_STATIC_ReadVal2, m_ReadVal[2]);
	DDX_Control(pDX, IDC_STATIC_ReadVal3, m_ReadVal[3]);
	DDX_Control(pDX, IDC_STATIC_ReadVal4, m_ReadVal[4]);
	DDX_Control(pDX, IDC_STATIC_ReadVal5, m_ReadVal[5]);
	DDX_Control(pDX, IDC_STATIC_ReadVal6, m_ReadVal[6]);
	DDX_Control(pDX, IDC_STATIC_ReadVal7, m_ReadVal[7]);
	DDX_Control(pDX, IDC_STATIC_ReadVal8, m_ReadVal[8]);
	DDX_Control(pDX, IDC_STATIC_ReadVal9, m_ReadVal[9]);
	//
	DDX_Control(pDX, IDC_STATIC_ReadName0, m_ReadName[0]);
	DDX_Control(pDX, IDC_STATIC_ReadName1, m_ReadName[1]);
	DDX_Control(pDX, IDC_STATIC_ReadName2, m_ReadName[2]);
	DDX_Control(pDX, IDC_STATIC_ReadName3, m_ReadName[3]);
	DDX_Control(pDX, IDC_STATIC_ReadName4, m_ReadName[4]);
	DDX_Control(pDX, IDC_STATIC_ReadName5, m_ReadName[5]);
	DDX_Control(pDX, IDC_STATIC_ReadName6, m_ReadName[6]);
	DDX_Control(pDX, IDC_STATIC_ReadName7, m_ReadName[7]);
	DDX_Control(pDX, IDC_STATIC_ReadName8, m_ReadName[8]);
	DDX_Control(pDX, IDC_STATIC_ReadName9, m_ReadName[9]);
}

BEGIN_MESSAGE_MAP(CMeterModbusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Read, &CMeterModbusDlg::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_OpenCom, &CMeterModbusDlg::OnBnClickedButtonOpencom)
	ON_BN_CLICKED(IDC_BUTTON_CloseCom, &CMeterModbusDlg::OnBnClickedButtonClosecom)
	ON_BN_CLICKED(IDC_BUTTON_ReadClear, &CMeterModbusDlg::OnBnClickedButtonReadclear)
	ON_CBN_SELCHANGE(IDC_COMBO_StopBit, &CMeterModbusDlg::OnCbnSelchangeComboStopbit)
	ON_BN_CLICKED(IDC_CHECK_def, &CMeterModbusDlg::OnBnClickedCheckdef)
	ON_EN_CHANGE(IDC_EDIT_MeterAdd, &CMeterModbusDlg::OnEnChangeEditMeteradd)
	ON_NOTIFY(NM_CLICK, IDC_TREE_Meter, &CMeterModbusDlg::OnNMClickTreeMeter)
	ON_EN_CHANGE(IDC_EDIT_TimeOuts, &CMeterModbusDlg::OnEnChangeEditTimeouts)
	ON_BN_CLICKED(IDC_CHECK_TimerRead, &CMeterModbusDlg::OnBnClickedCheckTimerread)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_TimerSet, &CMeterModbusDlg::OnEnChangeEditTimerset)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMeterModbusDlg 消息处理程序

BOOL CMeterModbusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	WarnFont.CreateFont(14,0, 0, 0, FW_BOLD,FALSE, FALSE,0, 
     ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
     DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,  _T("Arial")); 
	PromptFont.CreateFont(14,0, 0, 0, FW_BOLD,FALSE, FALSE,0, 
     ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
     DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,  _T("Arial")); 

	m_ColorText = RGB(0,0,255);
	m_ColorTextBK = RGB(255,255,255);
	m_pColorBrush = new CBrush(RGB(0,0,0));

	DialogInitial();
	Stopping();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMeterModbusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMeterModbusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMeterModbusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMeterModbusDlg::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	char tmpNumStr[10];
	memset(tmpNumStr,'/0',10);
	//
	OVERLAPPED m_osWrite; 
	memset(&m_osWrite,0,sizeof(OVERLAPPED)); 
	m_osWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL); 

	DWORD dwBytesWrite=8; 
	COMSTAT ComStat; 
	DWORD dwErrorFlags; 
	BOOL bWriteStat; 
	ClearCommError(hCom,&dwErrorFlags,&ComStat); 

	GetMeterReadCmd();

	bWriteStat=WriteFile(hCom,MeterReadCmdLine, 
		dwBytesWrite,& dwBytesWrite,&m_osWrite); 
	if(!bWriteStat) 
	{ 
		if(GetLastError()==ERROR_IO_PENDING) 
		{ 
			WaitForSingleObject(m_osWrite.hEvent,1000); 
		} 
	} 
	ReadCmdSendTimes++;
	itoa(ReadCmdSendTimes,tmpNumStr,10);
	GetDlgItem(IDC_STATIC_ReadNum)->SetWindowText(tmpNumStr); 
	//
	Sleep(50);
	//读取
	//
	DWORD dwStart = GetTickCount();
	DWORD dwEnd = dwStart;
	//
	OVERLAPPED m_osRead; 
	memset(&m_osRead,0,sizeof(OVERLAPPED)); 
	m_osRead.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL); 
	//COMSTAT ComStat; 
	//DWORD dwErrorFlags; 
	unsigned char recvstr[100]; 
	unsigned char strTest[100]; 
	CString strtemp;
	memset(recvstr,'\0',100); 
	memset(strTest,'\0',100);
	DWORD dwBytesRead=100;//读取的字节数 
	BOOL bReadStat; 
	//
	//do
	//{
		dwEnd = GetTickCount()-dwStart;
				
		ClearCommError(hCom,&dwErrorFlags,&ComStat); 
		dwBytesRead=min(dwBytesRead,(DWORD)ComStat.cbInQue); 
		bReadStat=ReadFile(hCom,recvstr, 
			dwBytesRead,&dwBytesRead,&m_osRead); 
		if(!bReadStat) 
		{ 
			if(GetLastError()==ERROR_IO_PENDING) 
				//GetLastError() 函数返回ERROR_IO_PENDING,表明串口正在进行读操作 
			{ 
				WaitForSingleObject(m_osRead.hEvent,2000); 
				//使用 WaitForSingleObject 函数等待,直到读操作完成或延时已达到 2 秒钟 
				//当串口读操作进行完毕后,m_osRead 的 hEvent 事件会变为有信号 
			} 
		} 

	//}while((dwEnd<2000) && (*recvstr==*strTest));

	//CheckSysError();

	if (!GetLastError())
	{
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("通讯正常！");
		Set_ComState_Green();
	}
	//
	if (*recvstr==*strTest)
	{
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("读取数据超时!");
		Set_ComState_Red();
		for(int i=0;i<10;i++)
		{
			m_ReadVal[i].SetWindowTextA("------");
		}
		return;
	}
	//
	PurgeComm(hCom,PURGE_TXABORT| 
		PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR); 
	//
	if (ReceiveDataCheck(recvstr))
	{
		ReadCmdReceiveTimes++;
		itoa(ReadCmdReceiveTimes,tmpNumStr,10);
		GetDlgItem(IDC_STATIC_ReceiveNum)->SetWindowText(tmpNumStr); 
		ViewReadData(recvstr);
	}
}


void CMeterModbusDlg::OnBnClickedButtonOpencom()
{
	// TODO: 在此添加控件通知处理程序代码
	//配置文件接口数据
	((CStatic*)GetDlgItem(IDC_STATIC_SelectMeter))->GetWindowText(SelectMeter);
	SelectMeter = ".\\MeterCfg\\" + SelectMeter + ".ini";
	//
	if (!ReadCFG(SelectMeter))
	{
		MessageBox("读取仪表配置文件失败！请选择正确的仪表配置文件。"); 
		return;
	}
	//读界面设置串口数据
	CString strDlg;
	((CEdit*)GetDlgItem(IDC_EDIT_TimeOuts))->GetWindowText(strDlg);
	ReceiveOutTimes = atoi(strDlg);
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->GetWindowText(SelectCom);
	//
	OnBnClickedCheckdef();
	//设置界面值与配置文件一致
	int i = 0;
	//GetDlgItem(IDC_COMBO_StopBit)->SetWindowText(MeterStopBit);
	i = ((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->FindStringExact(0,MeterParity);
	((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->SetCurSel(i);
	i = ((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->FindStringExact(0,MeterBands);
	((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->SetCurSel(i);
	i = ((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->FindStringExact(0,MeterStopBit);
	((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->SetCurSel(i);
	i = ((CComboBox*)GetDlgItem(IDC_COMBO_Bytes))->FindStringExact(0,MeterBytes);
	((CComboBox*)GetDlgItem(IDC_COMBO_Bytes))->SetCurSel(i);
	//根据配置默认框情况配置接口
	hCom=CreateFile(SelectCom,// 串口名称 
	GENERIC_READ|GENERIC_WRITE,//允许读和写 
	0,//独占方式 
	NULL, 
	OPEN_EXISTING,//打开而不是创建 
	FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,//重叠方式 
	NULL); 
	//
	if (hCom == INVALID_HANDLE_VALUE) 
	{ 
		//CheckSysError();
		MessageBox("打开"+SelectCom+"失败!"); 
		return;
	}
	//
	CString strtmp = "";
	strtmp.Format("串口%s已打开!",SelectCom);
	GetDlgItem(IDC_STATIC_ComState)->SetWindowText(strtmp);
	SetupComm(hCom,100,100);//输入缓冲区和输出缓冲区的大小都是 100 
	COMMTIMEOUTS TimeOuts; 
	//设定读超时 
	TimeOuts.ReadIntervalTimeout=MAXDWORD; 
	TimeOuts.ReadTotalTimeoutMultiplier=0; 
	TimeOuts.ReadTotalTimeoutConstant=ReceiveOutTimes;
	//在读一次输入缓冲区的内容后读操作就立即返回, 
	//而不管是否读入了要求的字符. 
	//设定写超时 
	TimeOuts.WriteTotalTimeoutMultiplier=100; 
	TimeOuts.WriteTotalTimeoutConstant=500; 
	SetCommTimeouts(hCom,&TimeOuts);//设置超时 
	DCB dcb; 
	GetCommState(hCom,&dcb); 
	//
	dcb.BaudRate=atoi(SelectBands);//波特率为 9600 
	dcb.ByteSize=atoi(SelectBytes);//每个字节有 8 位 
	if (strcmp(SelectParity,"NONE")){dcb.Parity=NOPARITY;}
	if (strcmp(SelectParity,"ODD")){dcb.Parity=ODDPARITY;}
	if (strcmp(SelectParity,"EVEN")){dcb.Parity=EVENPARITY;}
	//无奇偶校验位 
	dcb.StopBits=atoi(SelectStopBit);//两个停止位 
	SetCommState(hCom,&dcb); 
	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
	//
	Working();
	//
	ViewReadData(NULL);
}


void CMeterModbusDlg::OnBnClickedButtonClosecom()
{
	// TODO: 在此添加控件通知处理程序代码
	bool CloseOK;
	CloseOK = false;
	CloseOK = CloseHandle(hCom);//程序退出时关闭串口 
	if (CloseOK)
	{
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("串口已关闭!");
		Stopping();
		GetDlgItem(IDC_BUTTON_OpenCom)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON_CloseCom)->EnableWindow(0);
		//
		((CButton*)GetDlgItem(IDC_CHECK_TimerRead))->SetCheck(0);
		GetDlgItem(IDC_CHECK_TimerRead)->EnableWindow(0);
		OnBnClickedCheckTimerread();
		//
		Stopping();
	}
}

// 检查系统错误。并弹出对话框显示。
void CMeterModbusDlg::CheckSysError(void)
{
		LPVOID lpMsgBuf; 
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL, 
			GetLastError(), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language 
			(LPTSTR) &lpMsgBuf, 
			0, 
			NULL 
			); 
		// Process any inserts in lpMsgBuf. 
		//显示错误信息 
		MessageBox(  (LPCTSTR)lpMsgBuf); 

		// Free the buffer. 
		LocalFree( lpMsgBuf ); 
}


void CMeterModbusDlg::OnBnClickedButtonReadclear()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0;i<10;i++)
	{
		m_ReadVal[i].SetWindowTextA("------");
	}
	//
	GetDlgItem(IDC_STATIC_ReceiveNum)->SetWindowText("0"); 
	GetDlgItem(IDC_STATIC_ReadNum)->SetWindowText("0"); 
	//
	ReadCmdSendTimes = 0;
	ReadCmdReceiveTimes = 0;
}


void CMeterModbusDlg::OnCbnSelchangeComboStopbit()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMeterModbusDlg::DialogInitial(void)
{
	//遍历配置文件目录
	char *a=".\\MeterCfg\\*.ini";
	CFindFile findDemo;
	CString nFileName;
	for (findDemo.First(a); 
		findDemo.IsOK(); 
		findDemo.Next())
	{
		nFileName = findDemo.GetCurFile().cFileName;
		((CTreeCtrl*)GetDlgItem(IDC_TREE_Meter))->InsertItem(nFileName,0,1,TVI_ROOT,TVI_LAST);
//		cout<<findDemo.GetCurFile().cFileName;
//		cout<<"  xx\n";
	}
	//

	//
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->AddString("COM1");
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->AddString("COM2");
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->AddString("COM3");
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->AddString("COM4");
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->SetCurSel(0); 

	((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->AddString("4800");
	((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->AddString("9600");
	((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->AddString("14400");
	((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->SetCurSel(1); 

	((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->AddString("1");
	((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->AddString("1.5");
	((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->AddString("2");
	((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->AddString("NONE");
	((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->AddString("ODD");
	((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->AddString("EVEN");
	((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_Bytes))->AddString("8");
	((CComboBox*)GetDlgItem(IDC_COMBO_Bytes))->SetCurSel(0);
	//
	GetDlgItem(IDC_STATIC_ReceiveNum)->SetWindowText("0"); 
	GetDlgItem(IDC_STATIC_SelectMeter)->SetWindowText("-----");
	//
	((CEdit*)GetDlgItem(IDC_EDIT_MeterAdd))->SetWindowTextA("1");
	((CEdit*)GetDlgItem(IDC_EDIT_TimeOuts))->SetWindowTextA("1000");
	((CEdit*)GetDlgItem(IDC_EDIT_TimerSet))->SetWindowTextA("1000");
	//
	GetDlgItem(IDC_CHECK_TimerRead)->EnableWindow(0);
	//
	for (int i=0;i<10;i++)
	{
		MeterReceiveData_CfgName[i] = "";	
		MeterReceiveData_CfgType[i] = "";
	}
	//
	ReadCmdSendTimes = 0;
	ReadCmdReceiveTimes = 0;
	WriteCmdSendTimes = 0;
	ReceiveOutTimes = 0;
	//
	memset(MeterReadCmdLine,'\0',8);
	memset(MeterWriteCmdLine,'\0',8); 
	//
}


void CMeterModbusDlg::OnBnClickedCheckdef()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK_def))
	{
		GetDlgItem(IDC_COMBO_Bands)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_StopBit)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_Parity)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_Bytes)->EnableWindow(0);
		//
		((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->SetCurSel(1); 
		((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_COMBO_Bytes))->SetCurSel(0);
		//
		SelectBands = MeterBands;
		SelectParity = MeterParity;
		SelectStopBit = MeterStopBit;
		SelectBytes = MeterBytes;
	}
	else
	{
		GetDlgItem(IDC_COMBO_Bands)->EnableWindow(1);
		GetDlgItem(IDC_COMBO_StopBit)->EnableWindow(1);
		GetDlgItem(IDC_COMBO_Parity)->EnableWindow(1);
		GetDlgItem(IDC_COMBO_Bytes)->EnableWindow(1);
		//读取COM配置框数据
		((CComboBox*)GetDlgItem(IDC_COMBO_Bands))->GetWindowText(SelectBands);
		((CComboBox*)GetDlgItem(IDC_COMBO_Parity))->GetWindowText(SelectParity);
		((CComboBox*)GetDlgItem(IDC_COMBO_StopBit))->GetWindowText(SelectStopBit);
		((CComboBox*)GetDlgItem(IDC_COMBO_Bytes))->GetWindowText(SelectBytes);
	}
}


void CMeterModbusDlg::Working(void)
{
	GetDlgItem(IDC_BUTTON_OpenCom)->EnableWindow(0);
	GetDlgItem(IDC_BUTTON_CloseCom)->EnableWindow(1);

	GetDlgItem(IDC_BUTTON_Read)->EnableWindow(1);
	GetDlgItem(IDC_BUTTON_ReadClear)->EnableWindow(1);

	GetDlgItem(IDC_EDIT_MeterAdd)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TimeOuts)->EnableWindow(0);

	GetDlgItem(IDC_CHECK_TimerRead)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TimerSet)->EnableWindow(0);
	GetDlgItem(IDC_CHECK_def)->EnableWindow(0);
}

void CMeterModbusDlg::OnBnClickedButtonFindmeter()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CMeterModbusDlg::Stopping(void)
{
	GetDlgItem(IDC_BUTTON_OpenCom)->EnableWindow(1);
	GetDlgItem(IDC_BUTTON_CloseCom)->EnableWindow(0);

	GetDlgItem(IDC_BUTTON_Read)->EnableWindow(0);
	GetDlgItem(IDC_BUTTON_ReadClear)->EnableWindow(0);

	GetDlgItem(IDC_EDIT_MeterAdd)->EnableWindow(0);
	((CButton*)GetDlgItem(IDC_CHECK_def))->SetCheck(1);
	GetDlgItem(IDC_EDIT_TimerSet)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TimeOuts)->EnableWindow(1);

	GetDlgItem(IDC_CHECK_def)->EnableWindow(1);

	OnBnClickedCheckdef();
}


void CMeterModbusDlg::OnEnChangeEditMeteradd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString tmpstr;
	((CEdit*)GetDlgItem(IDC_EDIT_MeterAdd))->GetWindowText(tmpstr);
	MeterAdd = atoi(tmpstr);
	if ((MeterAdd <0) || (MeterAdd >255))  { MessageBox("仪表地址不正确！");}
}


void CMeterModbusDlg::GetMeterReadCmd(void)
{
	//
	BYTE str[8];
	memset(str,'\0',8);
	//
	CString tmpstr;
	((CEdit*)GetDlgItem(IDC_EDIT_MeterAdd))->GetWindowText(tmpstr);
	MeterAdd = atoi(tmpstr);
	//
	str[0]=MeterAdd;
	//
	str[1]=atoi(MeterReadCmd);
	//
	char ah;char al;
	//
	ah = '0';al = '0';
	ah = MeterReadStartAdd.GetAt(0);al = MeterReadStartAdd.GetAt(1);
	str[2]=strtol(&al,NULL,16)+strtol(&ah,NULL,16)*16;
	ah = '0';al = '0';
	ah = MeterReadStartAdd.GetAt(2);al = MeterReadStartAdd.GetAt(3);
	str[3]=strtol(&al,NULL,16)+strtol(&ah,NULL,16)*16;
	//
	ah = '0';al = '0';
	ah = MeterReadDataLen.GetAt(0);al = MeterReadDataLen.GetAt(1);
	str[4]=strtol(&al,NULL,16)+strtol(&ah,NULL,16)*16;
	ah = '0';al = '0';
	ah = MeterReadDataLen.GetAt(2);al = MeterReadDataLen.GetAt(3);
	str[5]=strtol(&al,NULL,16)+strtol(&ah,NULL,16)*16;
	//
	unsigned char crca[6];
	memcpy(crca,str,6);
	unsigned short crc;
	CNewCrc MyCrc;
	crc = MyCrc.ModBus_CRC(crca,6);
	str[6]=(crc&0xFF00)>>8; 
	str[7]=crc&0x00FF;
	//
	memset(MeterReadCmdLine,'\0',8);
	memcpy(MeterReadCmdLine,str,8);
}


void CMeterModbusDlg::ViewReadData(BYTE* str)
{
	if (str == NULL)
	{
		BYTE b[30];
		memset(b,'\0',30);
		str = b;
	}
	//
	CString tmpChar = 0;
	//初始化
	MeterReceiveDataLen = sizeof(*str);
	//读取仪表配置文件
	//
	int n = 0;
	int nbyte = 0;
	//
	while(n < 10)
	{
		tmpChar = "";
		nbyte = atoi(MeterReceiveData_CfgLocation[n]);
		//
		if((MeterReceiveData_CfgName[n] == "")||(MeterReceiveData_CfgType[n] == ""))
		{
			m_ReadVal[n].ShowWindow(0);
			m_ReadName[n].ShowWindow(0);
			n++;
			continue;
		}
		else
		{
			m_ReadName[n].SetWindowTextA(MeterReceiveData_CfgName[n]);
		}
		if (MeterReceiveData_CfgType[n] == "Binary")
		{
			int num=0;
			memcpy((BYTE*)&num+0,&str[nbyte+1],1);
			memcpy((BYTE*)&num+1,&str[nbyte],1);
			char buffer[20]; 
			memset(buffer,'\0',20);
			_itoa(num,buffer,2);
			tmpChar.Format(("%s"),buffer);
		}
		if (MeterReceiveData_CfgType[n] == "Decimal")
		{
			int num=0;
			memcpy((BYTE*)&num+0,&str[nbyte+1],1);
			memcpy((BYTE*)&num+1,&str[nbyte],1);
			tmpChar.Format(("%d"),num);
		}
		if (MeterReceiveData_CfgType[n] =="Hex")
		{
			int num=0;
			memcpy((BYTE*)&num+0,&str[nbyte+1],1);
			memcpy((BYTE*)&num+1,&str[nbyte],1);
			tmpChar.Format(("%X"),num);
		}
		if (MeterReceiveData_CfgType[n] =="Float")
		{
			float num=0;
			memcpy((BYTE*)&num+0,&str[nbyte+1],1);
			memcpy((BYTE*)&num+1,&str[nbyte],1);
			memcpy((BYTE*)&num+2,&str[nbyte+3],1);
			memcpy((BYTE*)&num+3,&str[nbyte+2],1);
			tmpChar.Format(("%f"),num);
		}
		if (MeterReceiveData_CfgType[n] =="BDC8421-2字节")
		{
			BYTE bytes[2];
			bytes[0]=str[nbyte];
			bytes[1]=str[nbyte+1];
			_int32 i32 = 0;

			byte i0;

			i0 = bytes[0]&0x0f; //按位与，i得到低四位数。
			bytes[0] >>= 4; //右移四位，将高四位移到低四位的位置，得到高四位码值。
			bytes[0] &= 0x0f; //防止移位时高位补进1，只保留高四位码值
			bytes[0] *= 10; //高位码值乘以10
			i0 += bytes[0]; //然后与第四位码值相加。
			i0=i0; //将得到的十进制数返回

			byte i1;
			i1 = bytes[1]&0x0f; //按位与，i得到低四位数。
			bytes[1] >>= 4; //右移四位，将高四位移到低四位的位置，得到高四位码值。
			bytes[1] &= 0x0f; //防止移位时高位补进1，只保留高四位码值
			bytes[1] *= 10; //高位码值乘以10
			i1 += bytes[1]; //然后与第四位码值相加。
			i1=i1; //将得到的十进制数返回

			i32 = i0 *100 +i1;
			//
			tmpChar.Format(("%d"),i32);
		}
		if (MeterReceiveData_CfgType[n] =="BDC8421-4字节")
		{
			BYTE bytes[4];
			bytes[0]=str[nbyte];
			bytes[1]=str[nbyte+1];
			bytes[2]=str[nbyte+2];
			bytes[3]=str[nbyte+3];
			_int32 i32 = 0;

			byte i0;
			i0 = bytes[0]&0x0f; //按位与，i得到低四位数。
			bytes[0] >>= 4; //右移四位，将高四位移到低四位的位置，得到高四位码值。
			bytes[0] &= 0x0f; //防止移位时高位补进1，只保留高四位码值
			bytes[0] *= 10; //高位码值乘以10
			i0 += bytes[0]; //然后与第四位码值相加。
			i0=i0; //将得到的十进制数返回

			byte i1;
			i1 = bytes[1]&0x0f; //按位与，i得到低四位数。
			bytes[1] >>= 4; //右移四位，将高四位移到低四位的位置，得到高四位码值。
			bytes[1] &= 0x0f; //防止移位时高位补进1，只保留高四位码值
			bytes[1] *= 10; //高位码值乘以10
			i1 += bytes[1]; //然后与第四位码值相加。
			i1=i1; //将得到的十进制数返回

			byte i2;
			i2 = bytes[2]&0x0f; //按位与，i得到低四位数。
			bytes[2] >>= 4; //右移四位，将高四位移到低四位的位置，得到高四位码值。
			bytes[2] &= 0x0f; //防止移位时高位补进1，只保留高四位码值
			bytes[2] *= 10; //高位码值乘以10
			i2 += bytes[2]; //然后与第四位码值相加。
			i2=i2; //将得到的十进制数返回

			byte i3;
			i3 = bytes[3]&0x0f; //按位与，i得到低四位数。
			bytes[3] >>= 4; //右移四位，将高四位移到低四位的位置，得到高四位码值。
			bytes[3] &= 0x0f; //防止移位时高位补进1，只保留高四位码值
			bytes[3] *= 10; //高位码值乘以10
			i3 += bytes[3]; //然后与第四位码值相加。
			i3=i3; //将得到的十进制数返回

			i32 = i0 *1000000 +i1*10000+i2*100+i3;
			//
			tmpChar.Format(("%d"),i32);
		}
		//
		m_ReadVal[n].SetWindowText(tmpChar);
		n = n + 1;
	}
}


bool CMeterModbusDlg::ReadCFG(CString FileName)
{
	// TODO: 在此添加控件通知处理程序代码
	setlocale(LC_ALL,"Chinese-simplified");
	//
	const int MAX=100;
	char buffer[MAX];
	CString strtmp;
	
	ifstream infile(FileName);
	
	if(!infile)	{return false;}

	while(infile)
	{
		memset(buffer,'\0',MAX);
		strtmp = "";
		infile.getline(buffer,MAX);
		strtmp = buffer;
		strtmp.Remove(' ');
		if ((strtmp[0] == '/') && (strtmp[1] == '/')){continue;}
		if (strtmp.GetLength() < 4){continue;}
		if (!(strtmp.Find((CString)"//") == -1))
		{
			strtmp = strtmp.Left(strtmp.Find((CString)";"));
		}
		//MessageBox(strtmp.Left(strtmp.Find(';')));
		strtmp.Remove(';');
		//
		if (strtmp.Left(strtmp.Find(':')) == "波特率")
		{
			MeterBands = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		} 
		//
		if (strtmp.Left(strtmp.Find(':')) == "停止位")
		{
			MeterStopBit = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		} 
		if (strtmp.Left(strtmp.Find(':')) == "效验")
		{
			MeterParity = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		if (strtmp.Left(strtmp.Find(':')) == "字长")
		{
			MeterBytes = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		//
		if (strtmp.Left(strtmp.Find(':')) == "仪表读取命令")
		{
			MeterReadCmd = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		//
		if (strtmp.Left(strtmp.Find(':')) == "读取起始地址")
		{
			MeterReadStartAdd = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		if (strtmp.Left(strtmp.Find(':')) == "读取数据字长")
		{
			MeterReadDataLen = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		// 
		for (int i =0;i<10;i++)
		{
			CString str;
			str = "";
			str.Format(_T("回送数据%d名称"),i+1);
			if (strtmp.Left(strtmp.Find(':')) == str)
			{
				MeterReceiveData_CfgName[i] = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
			}
		}
		for (int i =0;i<10;i++)
		{
			CString str;
			str = "";
			str.Format(_T("回送数据%d数据位置"),i+1);
			if (strtmp.Left(strtmp.Find(':')) == str)
			{
				MeterReceiveData_CfgLocation[i] = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
			}
		}
		for (int i =0;i<10;i++)
		{
			CString str;
			str = "";
			str.Format(_T("回送数据%d数据类型"),i+1);
			if (strtmp.Left(strtmp.Find(':')) == str)
			{
				MeterReceiveData_CfgType[i] = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
			}
		}
	}
	//
	if (!(MeterReadCmd == "01") && !(MeterReadCmd == "02") && !(MeterReadCmd == "03") && !(MeterReadCmd == "04"))
	{
		MessageBox("读配置文件错误!读取命令不正确！");
		return false;
	}
	if ((MeterReadStartAdd.GetLength() > 4) || atoi(MeterReadStartAdd) > 65535 || atoi(MeterReadStartAdd) < 0 || MeterReadStartAdd == "")
	{
		MessageBox("读配置文件错误!读取起始地址不正确！");
		return false;
	}
	if (atoi(MeterReadDataLen) > 10 || atoi(MeterReadDataLen) < 1 || (MeterReadDataLen.GetLength() < 4))
	{
		MeterReadDataLen = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		return false;
	}
	//
	if ( atoi(MeterBytes) > 10 || atoi(MeterBytes) < 1)
	{ 
		MessageBox("仪表配置文件中，读取数据不正确！");
		return false;
	}
	//
	//MeterReceiveDataLen = 4;
	//
	return true;
}


// 对接收的数据进行CRC效验
bool CMeterModbusDlg::ReceiveDataCheck(BYTE* str)
{
	int nLen = 0;
	//检测返回数据长度合法
	if ((!str[3] == atoi(MeterReadDataLen) * 2)){return 0;}
	//需效验数据长度 = 3+返回字节
	nLen = 3 + atoi(MeterReadDataLen) * 2;
	//nLen = 6;
	//
	unsigned char* pCrc = new unsigned char [nLen];
	memcpy(pCrc,&str[0],nLen);
	unsigned short crc;
	CNewCrc MyCrc;
	crc = MyCrc.ModBus_CRC(pCrc,nLen);

	//unsigned short crcTest;
	// 
	if (!(str[nLen] == ((crc&0xFF00)>>8))||!(str[nLen+1] ==(BYTE)(crc&0x00FF)))
	{
		//MessageBox("返回数据效验失败!");
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("返回数据效验失败!");
		Set_ComState_Red();
		return false;
	}
		if (crc == 0)
	{
		//MessageBox("返回数据效验失败!");
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("返回数据效验失败!");
		Set_ComState_Red();
		return false;
	}
	//
	delete[] pCrc;
	return true;
}


void CMeterModbusDlg::OnNMClickTreeMeter(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//单击CTreeCtrl的项时，用 
	HTREEITEM   hm; 
	hm =((CTreeCtrl*)GetDlgItem(IDC_TREE_Meter))->GetSelectedItem();
	CString strtmp = "";
	strtmp=((CTreeCtrl*)GetDlgItem(IDC_TREE_Meter))->GetItemText(hm);
	strtmp = strtmp.Left(strtmp.Find('.'));
	GetDlgItem(IDC_STATIC_SelectMeter)->SetWindowText(strtmp);
}


void CMeterModbusDlg::OnEnChangeEditTimeouts()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString tmpstr;
	int tmpint;
	((CEdit*)GetDlgItem(IDC_EDIT_TimeOuts))->GetWindowText(tmpstr);
	tmpint = atoi(tmpstr);
	if ((tmpint <500) || (tmpint >10000))  { MessageBox("接收超时时间输入不正确！");}
}




void CMeterModbusDlg::OnBnClickedCheckTimerread()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tmpstr;
	GetDlgItem(IDC_EDIT_TimerSet)->GetWindowText(tmpstr);
	SendIntervalTimes = atoi(tmpstr);
	//
	if(IsDlgButtonChecked(IDC_CHECK_TimerRead))
	{
		SetTimer(1,SendIntervalTimes,NULL);
		GetDlgItem(IDC_BUTTON_Read)->EnableWindow(0);
		//MessageBox("定时器启动");
	}
	else
	{
		KillTimer(1);
		GetDlgItem(IDC_BUTTON_Read)->EnableWindow(1);
		//MessageBox("定时器停止");
	}
}


void CMeterModbusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnTimer(nIDEvent);
	//
	OnBnClickedButtonRead();	
}


void CMeterModbusDlg::OnEnChangeEditTimerset()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString tmpstr;
	int tmpint;
	((CEdit*)GetDlgItem(IDC_EDIT_TimerSet))->GetWindowText(tmpstr);
	tmpint = atoi(tmpstr);
	if ((tmpint <500) || (tmpint >10000))  { MessageBox("定时发送时间输入不正确！");}
}


void CMeterModbusDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	delete m_pColorBrush;
}


HBRUSH CMeterModbusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF ColorTemp;

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_ComState:
		// Set color to green on black and return the background brush.
		pDC->SetTextColor(m_ColorText);
		//pDC->SetBkColor(m_ColorTextBK);
		//return (HBRUSH)(m_pColorBrush->GetSafeHandle());
		return hbr;
		break;
	case IDC_STATIC_SelectMeter:
		pDC->SetTextColor(RGB(0,0,255));
		return hbr;
		break;
	//case IDC_STATIC_Contact:
	//	pDC->SetTextColor(RGB(0,0,255));
	//	return hbr;
	//	break;
	//case IDC_STATIC_Note:
	//	pDC->SetTextColor(RGB(0,0,255));
	//	return hbr;
	//	break;
	default:
		return hbr;
	}
}

void CMeterModbusDlg::Set_ComState_Red()
{
	m_ColorText = RGB(255,0,0);
	// redraw edit control
	((CEdit *)GetDlgItem(IDC_STATIC_ComState))->SetRedraw(TRUE);
	// invalidate the entire control, force painting
	((CEdit *)GetDlgItem(IDC_STATIC_ComState))->Invalidate();
	((CEdit *)GetDlgItem(IDC_STATIC_ComState))->UpdateWindow();
	m_ColorText = RGB(0,0,0);
}

void CMeterModbusDlg::Set_ComState_Green()
{
	m_ColorText = RGB(0,0,255);
	// redraw edit control
	((CEdit *)GetDlgItem(IDC_STATIC_ComState))->SetRedraw(TRUE);
	// invalidate the entire control, force painting
	((CEdit *)GetDlgItem(IDC_STATIC_ComState))->Invalidate();
	((CEdit *)GetDlgItem(IDC_STATIC_ComState))->UpdateWindow();
	m_ColorText = RGB(0,0,0);
}