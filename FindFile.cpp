#include "StdAfx.h"
#include "FindFile.h"
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<winbase.h>
#include<string.h>
using namespace std; 

//����һ��Ŀ¼���ļ���


CFindFile::CFindFile(void)
{
	m_hFind = INVALID_HANDLE_VALUE;
	m_bFound = false;
	memset(&m_FindFileData,0,sizeof(m_FindFileData));
}
CFindFile::~CFindFile(void)
{
	if (m_hFind != INVALID_HANDLE_VALUE)
	{
		::FindClose(m_hFind);
	}
}
//�ҵ���һ���ļ���
void CFindFile::First(LPCTSTR lpFileName)
{
	m_hFind = ::FindFirstFile(lpFileName,&m_FindFileData);
	if (m_hFind != INVALID_HANDLE_VALUE)
	{
		m_bFound = true;
	}
	else
	{
		m_bFound = false;
	}
}
//����һ���ļ���
void CFindFile::Next(void)
{
	m_bFound = FindNextFile(m_hFind, &m_FindFileData) ? true:false;
}
//�Ƿ���Բ���һ���ļ���
bool CFindFile::IsOK(void)const 
{
	return m_bFound;
}
//���ص�ǰ�ļ������ԡ�
const WIN32_FIND_DATA& CFindFile::GetCurFile(void) 
{
	return m_FindFileData;
}


