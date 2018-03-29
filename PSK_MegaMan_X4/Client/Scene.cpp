#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
	:m_bIsInit(false)
{
}


CScene::~CScene()
{
}

void CScene::LateInit()
{
	if (!m_bIsInit)
		this->LateInit();
	m_bIsInit = true;
}

void CScene::DrawBackground(HDC hDC, const TCHAR* szName)
{
	CMyBmp* pBackGround = BmpManager->FindImage(szName);

	GdiTransparentBlt(hDC, 0, 0, BUFCX, BUFCY, pBackGround->GetMemDC(), 0, 0, pBackGround->GetBmpCX(), pBackGround->GetBmpCY(), RGB(255, 0, 255));
}

void CScene::DrawBackground(HDC hDC, const TCHAR * szName, float fScrollX, float fScrollY)
{
	// 이미지 : 화면 = 1 : 4 비율
	// 화면에서 400의 스크롤을 가면 이미지에서는 100의 스크롤을 가야함
	// 그리는 방식을 잘못 이해하고 있었음 - 

	CMyBmp* pBackGround = BmpManager->FindImage(szName);

	int iSizeX = (int) (fScrollX != 0 ? fScrollX : 0);
	int iSizeY = (int) (fScrollY != 0 ? fScrollY : 0);

	GdiTransparentBlt(hDC, 0, 0, BUFCX, BUFCY, pBackGround->GetMemDC(), (int)fScrollX , (int)fScrollY, BUFCX, BUFCY, RGB(255, 0, 255));
}
