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
	HANDLE m_hFind; //���浱���ҵ�λ�þ����
	bool m_bFound; //��ǰ�����Ƿ�ɹ���
	WIN32_FIND_DATA m_FindFileData;//���浱ǰ�ļ������ԡ�
};

