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
	BmpManager->AddBitMap(L"../MyResource/BG/BG_WHITE.bmp", L"BG_WHITE");
	BmpManager->AddBitMap(L"../MyResource/BG/BG_BLACK.bmp", L"BG_BLACK");
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE.bmp", L"BG_TITLE");
	SceneManager->ChangeScene(CSceneManager::MENU);
}

void CMainGame::LateInit()
{
}

void CMainGame::Update()
{
	SceneManager->Update();
}

void CMainGame::LateUpdate()
{
	SceneManager->LateUpdate();
	KeyManager->Update();
}

void CMainGame::Render()
{
	CMyBmp* pBackBuffer = BmpManager->FindImage(L"BG_BLACK");
	if (pBackBuffer == nullptr)
		return;

	HDC hBackBuffer = pBackBuffer->GetMemDC();

	CMyBmp* pBackGround = BmpManager->FindImage(L"BG_TITLE");
	if (pBackGround == nullptr)
		return;

	GdiTransparentBlt(hBackBuffer, 0, 0, BUFCX, BUFCY, pBackGround->GetMemDC(), 0, 0, pBackGround->GetBmpCX(), pBackGround->GetBmpCY(), RGB(255, 0, 255));
	//BitBlt(hBackBuffer, 0, 0, g_lWINCX, g_lWINCY, pBackGround->GetMemDC(), 0, 0, SRCCOPY);
	SceneManager->Render(hBackBuffer);
	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
	//BitBlt(m_hDC, 0, 0, g_lWINCX, g_lWINCY, hBackBuffer, 0, 0, SRCCOPY);
	GdiTransparentBlt(m_hDC, 0, 0, g_lWINCX, g_lWINCY, hBackBuffer, 0, 0, BUFCX, BUFCY, RGB(255, 0, 255));

}

void CMainGame::Release()
{
	SceneManager->DestroyInstance();
	BmpManager->DestroyInstance();
	KeyManager->DestroyInstance();
	GameManager->DestroyInstance();
}

void CMainGame::ResetMainDC()
{
	DeleteDC(m_hDC);
	HDC hDC = GetDC(g_hWnd);
	m_hDC = hDC;
}
