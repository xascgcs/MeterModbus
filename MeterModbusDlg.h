
// MeterModbusDlg.h : ͷ�ļ�
//

#pragma once


// CMeterModbusDlg �Ի���
class CMeterModbusDlg : public CDialogEx
{
// ����
public:
	CMeterModbusDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_METERMODBUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	//h
	HANDLE hCom;
	unsigned int SendNum;
	unsigned int ReciveNum;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonOpencom();
	afx_msg void OnBnClickedButtonClosecom();
	// ���ϵͳ���󡣲������Ի�����ʾ��
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
	unsigned int MeterReceiveDataLen;		//�����ֽ���	1�ֽڣ����ֵΪ20��
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
	bool ReadCFG(CString FileName);//��ȡ�����Ǳ��ļ�
	//
	CString MeterCom;
	int MeterAdd;//�Ǳ�Modbus��ַ������ʱָ����
	BYTE MeterReadCmdLine[8];
	unsigned char	MeterWriteCmdLine[15];
	//�����ļ��ӿ�

	//���ڲ�������
	CString MeterBands;
	CString MeterStopBit;
	CString MeterBytes;
	CString MeterParity;
	//��ȡ�Ǳ��������
	CString MeterReadCmd;
	CString MeterReadStartAdd;
	CString MeterReadDataLen;
	//
	CString	MeterReceiveData_CfgName[10];	//CSting����ʾ��������="���ſ���״̬"
	CString	MeterReceiveData_CfgLocation[10];
	CString MeterReceiveData_CfgType[10];
	// �Խ��յ����ݽ���CRCЧ��
	bool ReceiveDataCheck(BYTE* str);
	afx_msg void OnNMClickTreeMeter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditTimeouts();
	afx_msg void OnBnClickedCheckTimerread();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditTimerset();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
