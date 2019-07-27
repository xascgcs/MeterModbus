#pragma once
class CFindFile
{
public:
	CFindFile(void);
	~CFindFile(void);
	//
	void First(LPCTSTR lpFileName);
	void Next(void);
	bool IsOK(void) const;
	const WIN32_FIND_DATA& GetCurFile(void);
protected:
	HANDLE m_hFind; //保存当查找的位置句柄。
	bool m_bFound; //当前查找是否成功。
	WIN32_FIND_DATA m_FindFileData;//保存当前文件的属性。
};

