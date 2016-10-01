// CalPoint.h: interface for the CCalPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALPOINT_H__6CEAA0DE_9DF1_4698_971B_7086465AB312__INCLUDED_)
#define AFX_CALPOINT_H__6CEAA0DE_9DF1_4698_971B_7086465AB312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagCALPOINT{
	bool Vert;				// ������ �����������
	int LNum;				// ����� ������
	int PNum;				// ����� �����, ��� � �������� �����
	double x,y;
} CALPOINT, *PCALPOINT;

class CCalPoint{
public:
	CCalPoint();
	virtual ~CCalPoint();

};

#endif // !defined(AFX_CALPOINT_H__6CEAA0DE_9DF1_4698_971B_7086465AB312__INCLUDED_)
