
// MeterModbus.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMeterModbusApp:
// �йش����ʵ�֣������ MeterModbus.cpp
//

class CMeterModbusApp : public CWinApp
{
public:
	CMeterModbusApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMeterModbusApp theApp;