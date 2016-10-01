// Picture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__C2044CD1_8BCF_4022_82B5_561139D6B005__INCLUDED_)
#define AFX_PICTURE_H__C2044CD1_8BCF_4022_82B5_561139D6B005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define CLASS_TYPE_CXIMAGE		1
#define CLASS_TYPE_IPICTURE		2



class CPicture  
{
public:
	void GetBitmap(BITMAP	*pBmpInfo);
	BOOL IsValid();
	DWORD GetPictureHeight();
	DWORD GetPictureWidth();
	void SetZoom(double dZoom);
	double GetZoom();
	void Draw(HDC hDC, CRect ClientRect, CPoint ScrollPos);
	BOOL SetClassType(UINT nType);
	UINT GetClassType();
	BOOL Load(CString strFileName);
	CPicture();
	virtual ~CPicture();

protected:
	UINT m_nHeight;
	UINT m_nWidth;
	HRESULT FileToStream(LPCTSTR szFile, IStream* *ppStream);
	UINT m_nClassType;
	CxImage m_cxImage;
	CComPtr<IPicture> m_ptrPicture;
	double m_dZoom;
};

#endif // !defined(AFX_PICTURE_H__C2044CD1_8BCF_4022_82B5_561139D6B005__INCLUDED_)
