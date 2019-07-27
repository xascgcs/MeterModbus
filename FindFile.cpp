#include "StdAfx.h"
#include "FindFile.h"
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<winbase.h>
#include<string.h>
using namespace std; 

//遍历一个目录的文件。


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
//找到第一个文件。
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
//查找一下文件。
void CFindFile::Next(void)
{
	m_bFound = FindNextFile(m_hFind, &m_FindFileData) ? true:false;
}
//是否可以查找一下文件。
bool CFindFile::IsOK(void)const 
{
	return m_bFound;
}
//返回当前文件的属性。
const WIN32_FIND_DATA& CFindFile::GetCurFile(void) 
{
	return m_FindFileData;
}


