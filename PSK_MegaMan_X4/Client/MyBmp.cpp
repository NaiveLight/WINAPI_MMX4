#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::LoadBmp(const TCHAR * pFilePath)
{
	m_hDC = GetDC(g_hWnd);

	//CreateCompatibleDC : 현재 화면 DC와 호환되는 메모리 DC 할당
	m_hMemDC = CreateCompatibleDC(m_hDC);
	ReleaseDC(g_hWnd, m_hDC);

	m_hBitmap = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	BITMAP tempBmp = {};
	GetObject(m_hBitmap, sizeof(tempBmp), &tempBmp);

	lSizeX = tempBmp.bmWidth;
	lSizeY = tempBmp.bmHeight;
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOld);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
