#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Init()
{
	m_hDC = GetDC(g_hWnd);
	srand((unsigned)time(nullptr));
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE.bmp", L"BG_TITLE");
	BmpManager->AddBitMap(L"../MyResource/BG/BG_WHITE.bmp", L"BG_WHITE");
	BmpManager->AddBitMap(L"../MyResource/BG/BG_BLACK.bmp", L"BG_BLACK");
}

void CMainGame::LateInit()
{
}

void CMainGame::Update()
{
}

void CMainGame::LateUpdate()
{
}

void CMainGame::Render()
{
	CMyBmp* pBackBuffer = BmpManager->FindImage(L"BG_BLACK");
	if (pBackBuffer == nullptr)
		return;

	HDC hBackBuffer = pBackBuffer->GetMemDC();
	LONG lBufCX = pBackBuffer->GetBmpCX();
	LONG lBufCY = pBackBuffer->GetBmpCY();

	CMyBmp* pBackGround = BmpManager->FindImage(L"BG_TITLE");
	if (pBackGround == nullptr)
		return;

	GdiTransparentBlt(hBackBuffer, 0, 0, WINCX, WINCY, pBackGround->GetMemDC(), 0, 0, pBackGround->GetBmpCX(), pBackGround->GetBmpCY(), RGB(255, 255, 255));

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{

}
