// Picture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "corr.h"
#include "Picture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPicture::CPicture()
{
	m_nClassType=CLASS_TYPE_CXIMAGE;
//	m_nClassType=CLASS_TYPE_IPICTURE;
	m_dZoom=1;
	m_nHeight=m_nWidth=0;
}

CPicture::~CPicture()
{
	if(m_ptrPicture)
	{
		m_ptrPicture.Release();
	}
	if(m_cxImage.IsValid())
	{
		m_cxImage.Destroy();
	}
}

BOOL CPicture::Load(CString strFileName)
{
	BOOL	bRes=FALSE;
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
		if(m_cxImage.IsValid())
		{
			m_cxImage.Destroy();
		}
		bRes=m_cxImage.Load(strFileName);
		if(bRes)
		{
			m_nWidth=m_cxImage.GetWidth();
			m_nHeight=m_cxImage.GetHeight();
		}
		break;
	case CLASS_TYPE_IPICTURE:
		if(m_ptrPicture!=NULL)
		{
			m_ptrPicture.Release();
		}
		{
			CComPtr<IStream> pStream;
			// Load the file to a memory stream
			HRESULT hr=FileToStream(strFileName, &pStream);
			if(SUCCEEDED(hr))
			{
				// Decode the picture
				hr = ::OleLoadPicture(
						pStream,			// [in] Pointer to the stream that contains picture's data
						0,					// [in] Number of bytes read from the stream (0 == entire)
						true,				// [in] Loose original format if true
						IID_IPicture,		// [in] Requested interface
						(void**)&m_ptrPicture // [out] IPictire object on success
						);
				if(SUCCEEDED(hr))
				{
					return TRUE;
				}
			}
		}
		break;
	}
	return bRes;
}

UINT CPicture::GetClassType()
{
	return m_nClassType;
}

BOOL CPicture::SetClassType(UINT nType)
{
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
	case CLASS_TYPE_IPICTURE:
		m_nClassType=nType;
		return TRUE;
		break;
	}
	return FALSE;
}

void CPicture::Draw(HDC hDC, CRect ClientRect, CPoint ScrollPos)
{
	// Для удобвства создаем CDC
	// Создаем соответствующий Bitmap
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
		{
			// Рисуем
			CRect	tmpRect=ClientRect;
			tmpRect.OffsetRect(ScrollPos);
			// Пересчитываем вырезаемый прямоугольник согласно масштабу
			tmpRect.top=long(tmpRect.top/m_dZoom);
			tmpRect.left=long(tmpRect.left/m_dZoom);
			tmpRect.right=long(tmpRect.right/m_dZoom);
			if(tmpRect.Width()>(int)m_nWidth)
			{
				tmpRect.left=0;
				tmpRect.right=tmpRect.left+m_nWidth;
			}
			tmpRect.bottom=long(tmpRect.bottom/m_dZoom);
			if(tmpRect.Height()>(int)m_nHeight)
			{
				tmpRect.top=0;
				tmpRect.bottom=tmpRect.top+m_nHeight;
			}
			if((tmpRect.Width()>=(int)m_nWidth) && (tmpRect.Height()>=(int)m_nHeight))
			{
				m_cxImage.Draw2(hDC, ClientRect);
			}
			else
			{
				CxImage	tmpImage;
				// Зырезаем
				m_cxImage.Crop(tmpRect, &tmpImage);
				// Рисуем
				tmpImage.Draw2(hDC, ClientRect);
				// Удаляем временный объект
				tmpImage.Destroy();
			}
		}
		break;
	case CLASS_TYPE_IPICTURE:
		{
			// Размер рисунка
			long nWidth=GetPictureWidth();
			long nHeight=GetPictureHeight();
			// Размер рисунка в HIMETRIC
			long hmWidth = 0, hmHeight = 0;
			m_ptrPicture->get_Width(&hmWidth);
			m_ptrPicture->get_Height(&hmHeight);
			// Рисуем
			m_ptrPicture->Render(
				hDC,		// [in] Handle of device context on which to render the image
				0,					// [in] Horizontal position of image in hdc
				0,					// [in] Vertical position of image in hdc
				nWidth,				// [in] Horizontal dimension of destination rectangle
				nHeight,			// [in] Vertical dimension of destination rectangle
				0,					// [in] Horizontal offset in source picture
				hmHeight,			// [in] Vertical offset in source picture
				hmWidth,			// [in] Amount to copy horizontally in source picture
				-hmHeight,			// [in] Amount to copy vertically in source picture
				NULL				// [in, optional] Pointer to position of destination for a metafile hdc
				);
		}
		break;
	}
}

double CPicture::GetZoom()
{
	return m_dZoom;
}

void CPicture::SetZoom(double dZoom)
{
	m_dZoom=dZoom;
}

DWORD CPicture::GetPictureWidth()
{
/*
	if(!IsValid())return 0;
	DWORD	nWidth=0;
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
		nWidth=m_cxImage.GetWidth();
		break;
	case CLASS_TYPE_IPICTURE:
		{
			// Размер рисунка в HIMETRIC
			long hmWidth=0;
			m_ptrPicture->get_Width(&hmWidth);
			// HIMETRIC to pixels
			nWidth=MulDiv(hmWidth, GetDeviceCaps(::GetDC(NULL), LOGPIXELSX), HIMETRIC_PER_INCH);
		}
		break;
	}
	// Масштаб
	nWidth=(DWORD)(nWidth*m_dZoom);
*/
	return m_nWidth;
}

DWORD CPicture::GetPictureHeight()
{
/*
	if(!IsValid())return 0;
	DWORD	nHeight=0;
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
		nHeight=m_cxImage.GetHeight();
		break;
	case CLASS_TYPE_IPICTURE:
		{
			// Размер рисунка в HIMETRIC
			long hmHeight=0;
			m_ptrPicture->get_Height(&hmHeight);
			// HIMETRIC to pixels
			nHeight=MulDiv(hmHeight, GetDeviceCaps(::GetDC(NULL), LOGPIXELSY), HIMETRIC_PER_INCH);
		}
		break;
	}
	// Масштаб
	nHeight=(DWORD)(nHeight*m_dZoom);
*/
	return m_nHeight;
}

BOOL CPicture::IsValid()
{
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
		return m_cxImage.IsValid();
		break;
	case CLASS_TYPE_IPICTURE:
		if(m_ptrPicture)
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}

HRESULT CPicture::FileToStream(LPCTSTR szFile, IStream **ppStream)
{
	HRESULT hr;
	HGLOBAL hGlobal = NULL;

	// open file
	HANDLE hFile = ::CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return HRESULT_FROM_WIN32(::GetLastError());

	// get file size
	DWORD dwBytesRead = 0, dwFileSize = ::GetFileSize(hFile, NULL);
	if (-1 != dwFileSize)
	{
		hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
		if (NULL != hGlobal)
		{
			PVOID pvData = ::GlobalLock(hGlobal);
			ATLASSERT(NULL != pvData);

			// read file and store in global memory
			::ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
			::GlobalUnlock(hGlobal);

			if (dwFileSize != dwBytesRead)
			{
				::GlobalFree(hGlobal);
				hr = E_FAIL;
			}
			else
				hr = S_OK;
		}
		else
			hr = E_OUTOFMEMORY;
	}
	else
		hr = HRESULT_FROM_WIN32(::GetLastError());

	::CloseHandle(hFile);

	// create IStream* from global memory
	if (SUCCEEDED(hr))
		hr = ::CreateStreamOnHGlobal(hGlobal, TRUE, ppStream);
	return hr;
}

void CPicture::GetBitmap(BITMAP	*pBmpInfo)
{
	if(!IsValid())return;
	CBitmap	tmpBmp;
	switch(m_nClassType)
	{
	case CLASS_TYPE_CXIMAGE:
		tmpBmp.Attach(m_cxImage.MakeBitmap());
		tmpBmp.GetBitmap(pBmpInfo);
		tmpBmp.Detach();
		break;
	case CLASS_TYPE_IPICTURE:
		OLE_HANDLE	hOle;
		m_ptrPicture->get_Handle(&hOle);
		tmpBmp.Attach((HBITMAP)hOle);
		tmpBmp.GetBitmap(pBmpInfo);
		tmpBmp.Detach();
		break;
	}
}
