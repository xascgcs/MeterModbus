
// MeterModbusDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// CMeterModbusDlg �Ի���

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


// CMeterModbusDlg ��Ϣ�������

BOOL CMeterModbusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMeterModbusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMeterModbusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMeterModbusDlg::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//��ȡ
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
	DWORD dwBytesRead=100;//��ȡ���ֽ��� 
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
				//GetLastError() ��������ERROR_IO_PENDING,�����������ڽ��ж����� 
			{ 
				WaitForSingleObject(m_osRead.hEvent,2000); 
				//ʹ�� WaitForSingleObject �����ȴ�,ֱ����������ɻ���ʱ�Ѵﵽ 2 ���� 
				//�����ڶ�����������Ϻ�,m_osRead �� hEvent �¼����Ϊ���ź� 
			} 
		} 

	//}while((dwEnd<2000) && (*recvstr==*strTest));

	//CheckSysError();

	if (!GetLastError())
	{
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("ͨѶ������");
		Set_ComState_Green();
	}
	//
	if (*recvstr==*strTest)
	{
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("��ȡ���ݳ�ʱ!");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ļ��ӿ�����
	((CStatic*)GetDlgItem(IDC_STATIC_SelectMeter))->GetWindowText(SelectMeter);
	SelectMeter = ".\\MeterCfg\\" + SelectMeter + ".ini";
	//
	if (!ReadCFG(SelectMeter))
	{
		MessageBox("��ȡ�Ǳ������ļ�ʧ�ܣ���ѡ����ȷ���Ǳ������ļ���"); 
		return;
	}
	//���������ô�������
	CString strDlg;
	((CEdit*)GetDlgItem(IDC_EDIT_TimeOuts))->GetWindowText(strDlg);
	ReceiveOutTimes = atoi(strDlg);
	((CComboBox*)GetDlgItem(IDC_COMBO_ports))->GetWindowText(SelectCom);
	//
	OnBnClickedCheckdef();
	//���ý���ֵ�������ļ�һ��
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
	//��������Ĭ�Ͽ�������ýӿ�
	hCom=CreateFile(SelectCom,// �������� 
	GENERIC_READ|GENERIC_WRITE,//�������д 
	0,//��ռ��ʽ 
	NULL, 
	OPEN_EXISTING,//�򿪶����Ǵ��� 
	FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,//�ص���ʽ 
	NULL); 
	//
	if (hCom == INVALID_HANDLE_VALUE) 
	{ 
		//CheckSysError();
		MessageBox("��"+SelectCom+"ʧ��!"); 
		return;
	}
	//
	CString strtmp = "";
	strtmp.Format("����%s�Ѵ�!",SelectCom);
	GetDlgItem(IDC_STATIC_ComState)->SetWindowText(strtmp);
	SetupComm(hCom,100,100);//���뻺����������������Ĵ�С���� 100 
	COMMTIMEOUTS TimeOuts; 
	//�趨����ʱ 
	TimeOuts.ReadIntervalTimeout=MAXDWORD; 
	TimeOuts.ReadTotalTimeoutMultiplier=0; 
	TimeOuts.ReadTotalTimeoutConstant=ReceiveOutTimes;
	//�ڶ�һ�����뻺���������ݺ����������������, 
	//�������Ƿ������Ҫ����ַ�. 
	//�趨д��ʱ 
	TimeOuts.WriteTotalTimeoutMultiplier=100; 
	TimeOuts.WriteTotalTimeoutConstant=500; 
	SetCommTimeouts(hCom,&TimeOuts);//���ó�ʱ 
	DCB dcb; 
	GetCommState(hCom,&dcb); 
	//
	dcb.BaudRate=atoi(SelectBands);//������Ϊ 9600 
	dcb.ByteSize=atoi(SelectBytes);//ÿ���ֽ��� 8 λ 
	if (strcmp(SelectParity,"NONE")){dcb.Parity=NOPARITY;}
	if (strcmp(SelectParity,"ODD")){dcb.Parity=ODDPARITY;}
	if (strcmp(SelectParity,"EVEN")){dcb.Parity=EVENPARITY;}
	//����żУ��λ 
	dcb.StopBits=atoi(SelectStopBit);//����ֹͣλ 
	SetCommState(hCom,&dcb); 
	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
	//
	Working();
	//
	ViewReadData(NULL);
}


void CMeterModbusDlg::OnBnClickedButtonClosecom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool CloseOK;
	CloseOK = false;
	CloseOK = CloseHandle(hCom);//�����˳�ʱ�رմ��� 
	if (CloseOK)
	{
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("�����ѹر�!");
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

// ���ϵͳ���󡣲������Ի�����ʾ��
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
		//��ʾ������Ϣ 
		MessageBox(  (LPCTSTR)lpMsgBuf); 

		// Free the buffer. 
		LocalFree( lpMsgBuf ); 
}


void CMeterModbusDlg::OnBnClickedButtonReadclear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMeterModbusDlg::DialogInitial(void)
{
	//���������ļ�Ŀ¼
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//��ȡCOM���ÿ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmpstr;
	((CEdit*)GetDlgItem(IDC_EDIT_MeterAdd))->GetWindowText(tmpstr);
	MeterAdd = atoi(tmpstr);
	if ((MeterAdd <0) || (MeterAdd >255))  { MessageBox("�Ǳ��ַ����ȷ��");}
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
	//��ʼ��
	MeterReceiveDataLen = sizeof(*str);
	//��ȡ�Ǳ������ļ�
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
		if (MeterReceiveData_CfgType[n] =="BDC8421-2�ֽ�")
		{
			BYTE bytes[2];
			bytes[0]=str[nbyte];
			bytes[1]=str[nbyte+1];
			_int32 i32 = 0;

			byte i0;

			i0 = bytes[0]&0x0f; //��λ�룬i�õ�����λ����
			bytes[0] >>= 4; //������λ��������λ�Ƶ�����λ��λ�ã��õ�����λ��ֵ��
			bytes[0] &= 0x0f; //��ֹ��λʱ��λ����1��ֻ��������λ��ֵ
			bytes[0] *= 10; //��λ��ֵ����10
			i0 += bytes[0]; //Ȼ�������λ��ֵ��ӡ�
			i0=i0; //���õ���ʮ����������

			byte i1;
			i1 = bytes[1]&0x0f; //��λ�룬i�õ�����λ����
			bytes[1] >>= 4; //������λ��������λ�Ƶ�����λ��λ�ã��õ�����λ��ֵ��
			bytes[1] &= 0x0f; //��ֹ��λʱ��λ����1��ֻ��������λ��ֵ
			bytes[1] *= 10; //��λ��ֵ����10
			i1 += bytes[1]; //Ȼ�������λ��ֵ��ӡ�
			i1=i1; //���õ���ʮ����������

			i32 = i0 *100 +i1;
			//
			tmpChar.Format(("%d"),i32);
		}
		if (MeterReceiveData_CfgType[n] =="BDC8421-4�ֽ�")
		{
			BYTE bytes[4];
			bytes[0]=str[nbyte];
			bytes[1]=str[nbyte+1];
			bytes[2]=str[nbyte+2];
			bytes[3]=str[nbyte+3];
			_int32 i32 = 0;

			byte i0;
			i0 = bytes[0]&0x0f; //��λ�룬i�õ�����λ����
			bytes[0] >>= 4; //������λ��������λ�Ƶ�����λ��λ�ã��õ�����λ��ֵ��
			bytes[0] &= 0x0f; //��ֹ��λʱ��λ����1��ֻ��������λ��ֵ
			bytes[0] *= 10; //��λ��ֵ����10
			i0 += bytes[0]; //Ȼ�������λ��ֵ��ӡ�
			i0=i0; //���õ���ʮ����������

			byte i1;
			i1 = bytes[1]&0x0f; //��λ�룬i�õ�����λ����
			bytes[1] >>= 4; //������λ��������λ�Ƶ�����λ��λ�ã��õ�����λ��ֵ��
			bytes[1] &= 0x0f; //��ֹ��λʱ��λ����1��ֻ��������λ��ֵ
			bytes[1] *= 10; //��λ��ֵ����10
			i1 += bytes[1]; //Ȼ�������λ��ֵ��ӡ�
			i1=i1; //���õ���ʮ����������

			byte i2;
			i2 = bytes[2]&0x0f; //��λ�룬i�õ�����λ����
			bytes[2] >>= 4; //������λ��������λ�Ƶ�����λ��λ�ã��õ�����λ��ֵ��
			bytes[2] &= 0x0f; //��ֹ��λʱ��λ����1��ֻ��������λ��ֵ
			bytes[2] *= 10; //��λ��ֵ����10
			i2 += bytes[2]; //Ȼ�������λ��ֵ��ӡ�
			i2=i2; //���õ���ʮ����������

			byte i3;
			i3 = bytes[3]&0x0f; //��λ�룬i�õ�����λ����
			bytes[3] >>= 4; //������λ��������λ�Ƶ�����λ��λ�ã��õ�����λ��ֵ��
			bytes[3] &= 0x0f; //��ֹ��λʱ��λ����1��ֻ��������λ��ֵ
			bytes[3] *= 10; //��λ��ֵ����10
			i3 += bytes[3]; //Ȼ�������λ��ֵ��ӡ�
			i3=i3; //���õ���ʮ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		if (strtmp.Left(strtmp.Find(':')) == "������")
		{
			MeterBands = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		} 
		//
		if (strtmp.Left(strtmp.Find(':')) == "ֹͣλ")
		{
			MeterStopBit = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		} 
		if (strtmp.Left(strtmp.Find(':')) == "Ч��")
		{
			MeterParity = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		if (strtmp.Left(strtmp.Find(':')) == "�ֳ�")
		{
			MeterBytes = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		//
		if (strtmp.Left(strtmp.Find(':')) == "�Ǳ��ȡ����")
		{
			MeterReadCmd = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		//
		if (strtmp.Left(strtmp.Find(':')) == "��ȡ��ʼ��ַ")
		{
			MeterReadStartAdd = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		if (strtmp.Left(strtmp.Find(':')) == "��ȡ�����ֳ�")
		{
			MeterReadDataLen = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
		}
		// 
		for (int i =0;i<10;i++)
		{
			CString str;
			str = "";
			str.Format(_T("��������%d����"),i+1);
			if (strtmp.Left(strtmp.Find(':')) == str)
			{
				MeterReceiveData_CfgName[i] = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
			}
		}
		for (int i =0;i<10;i++)
		{
			CString str;
			str = "";
			str.Format(_T("��������%d����λ��"),i+1);
			if (strtmp.Left(strtmp.Find(':')) == str)
			{
				MeterReceiveData_CfgLocation[i] = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
			}
		}
		for (int i =0;i<10;i++)
		{
			CString str;
			str = "";
			str.Format(_T("��������%d��������"),i+1);
			if (strtmp.Left(strtmp.Find(':')) == str)
			{
				MeterReceiveData_CfgType[i] = strtmp.Mid(strtmp.Find(':') + 1,strtmp.GetLength() - strtmp.Find(':'));
			}
		}
	}
	//
	if (!(MeterReadCmd == "01") && !(MeterReadCmd == "02") && !(MeterReadCmd == "03") && !(MeterReadCmd == "04"))
	{
		MessageBox("�������ļ�����!��ȡ�����ȷ��");
		return false;
	}
	if ((MeterReadStartAdd.GetLength() > 4) || atoi(MeterReadStartAdd) > 65535 || atoi(MeterReadStartAdd) < 0 || MeterReadStartAdd == "")
	{
		MessageBox("�������ļ�����!��ȡ��ʼ��ַ����ȷ��");
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
		MessageBox("�Ǳ������ļ��У���ȡ���ݲ���ȷ��");
		return false;
	}
	//
	//MeterReceiveDataLen = 4;
	//
	return true;
}


// �Խ��յ����ݽ���CRCЧ��
bool CMeterModbusDlg::ReceiveDataCheck(BYTE* str)
{
	int nLen = 0;
	//��ⷵ�����ݳ��ȺϷ�
	if ((!str[3] == atoi(MeterReadDataLen) * 2)){return 0;}
	//��Ч�����ݳ��� = 3+�����ֽ�
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
		//MessageBox("��������Ч��ʧ��!");
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("��������Ч��ʧ��!");
		Set_ComState_Red();
		return false;
	}
		if (crc == 0)
	{
		//MessageBox("��������Ч��ʧ��!");
		GetDlgItem(IDC_STATIC_ComState)->SetWindowText("��������Ч��ʧ��!");
		Set_ComState_Red();
		return false;
	}
	//
	delete[] pCrc;
	return true;
}


void CMeterModbusDlg::OnNMClickTreeMeter(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//����CTreeCtrl����ʱ���� 
	HTREEITEM   hm; 
	hm =((CTreeCtrl*)GetDlgItem(IDC_TREE_Meter))->GetSelectedItem();
	CString strtmp = "";
	strtmp=((CTreeCtrl*)GetDlgItem(IDC_TREE_Meter))->GetItemText(hm);
	strtmp = strtmp.Left(strtmp.Find('.'));
	GetDlgItem(IDC_STATIC_SelectMeter)->SetWindowText(strtmp);
}


void CMeterModbusDlg::OnEnChangeEditTimeouts()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmpstr;
	int tmpint;
	((CEdit*)GetDlgItem(IDC_EDIT_TimeOuts))->GetWindowText(tmpstr);
	tmpint = atoi(tmpstr);
	if ((tmpint <500) || (tmpint >10000))  { MessageBox("���ճ�ʱʱ�����벻��ȷ��");}
}




void CMeterModbusDlg::OnBnClickedCheckTimerread()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tmpstr;
	GetDlgItem(IDC_EDIT_TimerSet)->GetWindowText(tmpstr);
	SendIntervalTimes = atoi(tmpstr);
	//
	if(IsDlgButtonChecked(IDC_CHECK_TimerRead))
	{
		SetTimer(1,SendIntervalTimes,NULL);
		GetDlgItem(IDC_BUTTON_Read)->EnableWindow(0);
		//MessageBox("��ʱ������");
	}
	else
	{
		KillTimer(1);
		GetDlgItem(IDC_BUTTON_Read)->EnableWindow(1);
		//MessageBox("��ʱ��ֹͣ");
	}
}


void CMeterModbusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnTimer(nIDEvent);
	//
	OnBnClickedButtonRead();	
}


void CMeterModbusDlg::OnEnChangeEditTimerset()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tmpstr;
	int tmpint;
	((CEdit*)GetDlgItem(IDC_EDIT_TimerSet))->GetWindowText(tmpstr);
	tmpint = atoi(tmpstr);
	if ((tmpint <500) || (tmpint >10000))  { MessageBox("��ʱ����ʱ�����벻��ȷ��");}
}


void CMeterModbusDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	delete m_pColorBrush;
}


HBRUSH CMeterModbusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	COLORREF ColorTemp;

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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