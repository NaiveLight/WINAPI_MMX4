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
	BmpManager->AddBitMap(L"../MyResource/BG/sz_BG_BLACK.bmp", L"BG_BLACK");
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE.bmp", L"BG_TITLE");
	SceneManager->ChangeScene(CSceneManager::STAGE1_1);
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
	SoundManager->Update();
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

	BitBlt(hBackBuffer, 0, 0, BUFCX, BUFCY, pBackGround->GetMemDC(), 0, 0, SRCCOPY);

	SceneManager->Render(hBackBuffer);
	GdiTransparentBlt(m_hDC, 0, 0, g_lWINCX, g_lWINCY, hBackBuffer, 0, 0, BUFCX, BUFCY, RGB(255, 0, 255));
}

void CMainGame::Release()
{
	SoundManager->DestroyInstance();
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
