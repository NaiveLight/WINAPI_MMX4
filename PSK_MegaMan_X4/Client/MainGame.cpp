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
}

void CMainGame::Release()
{
}
