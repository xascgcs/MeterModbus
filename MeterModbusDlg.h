
// MeterModbusDlg.h : 头文件
//

#pragma once


// CMeterModbusDlg 对话框
class CMeterModbusDlg : public CDialogEx
{
// 构造
public:
	CMeterModbusDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_METERMODBUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	//h
	HANDLE hCom;
	unsigned int SendNum;
	unsigned int ReciveNum;


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonOpencom();
	afx_msg void OnBnClickedButtonClosecom();
	// 检查系统错误。并弹出对话框显示。
	void CheckSysError(void);
	afx_msg void OnBnClickedButtonReadclear();
	afx_msg void OnCbnSelchangeComboStopbit();
	void DialogInitial(void);
	afx_msg void OnBnClickedCheckdef();
	void Working(void);
	afx_msg void OnBnClickedButtonFindmeter();
	void Stopping(void);
	afx_msg void OnCbnSelchangeComboBands();
	afx_msg void OnCbnSelchangeComboParity();
	//
	CStatic m_ReadName[10];
	CStatic m_ReadVal[10];
	//
	CString SelectCom;
	CString SelectBands;
	CString SelectStopBit;
	CString SelectBytes;
	CString SelectParity;
	//
	CString SelectMeter;
	//
	int ReadCmdSendTimes;
	int ReadCmdReceiveTimes;
	int WriteCmdSendTimes;
	int ReceiveOutTimes;
	int SendIntervalTimes;

	unsigned char	ResultData[29]; 
	afx_msg void OnEnChangeEditMeteradd();
	void GetMeterReadCmd(void);
	void ViewReadData(BYTE* str);
	//
	unsigned int MeterReceiveDataLen;		//返回字节数	1字节，最大值为20。
	//
	CFont WarnFont;
	CFont PromptFont;
	COLORREF m_ColorText;
	COLORREF m_ColorTextBK;
	CBrush* m_pColorBrush;
	//
	void Set_ComState_Red();
	void Set_ComState_Green();
	//
	bool ReadCFG(CString FileName);//读取配置仪表文件
	//
	CString MeterCom;
	int MeterAdd;//仪表Modbus地址。运行时指定。
	BYTE MeterReadCmdLine[8];
	unsigned char	MeterWriteCmdLine[15];
	//配置文件接口

	//串口参数配置
	CString MeterBands;
	CString MeterStopBit;
	CString MeterBytes;
	CString MeterParity;
	//读取仪表命令参数
	CString MeterReadCmd;
	CString MeterReadStartAdd;
	CString MeterReadDataLen;
	//
	CString	MeterReceiveData_CfgName[10];	//CSting。表示数据名称="阀门控制状态"
	CString	MeterReceiveData_CfgLocation[10];
	CString MeterReceiveData_CfgType[10];
	// 对接收的数据进行CRC效验
	bool ReceiveDataCheck(BYTE* str);
	afx_msg void OnNMClickTreeMeter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditTimeouts();
	afx_msg void OnBnClickedCheckTimerread();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditTimerset();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
