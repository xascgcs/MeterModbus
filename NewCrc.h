// NewCrc.h: interface for the CNewCrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWCRC_H__B4F02796_C6FC_4AA8_B705_7C5C82F0BD2E__INCLUDED_)
#define AFX_NEWCRC_H__B4F02796_C6FC_4AA8_B705_7C5C82F0BD2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNewCrc  
{
public:

	unsigned short ModBus_CRC(unsigned char *charSource, unsigned short iLength);

public:
	CNewCrc();
	virtual ~CNewCrc();

};

#endif // !defined(AFX_NEWCRC_H__B4F02796_C6FC_4AA8_B705_7C5C82F0BD2E__INCLUDED_)
