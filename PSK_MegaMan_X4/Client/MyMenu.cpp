#include "stdafx.h"
#include "MyMenu.h"
#include "MenuText.h"
#include "MenuUnder.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE_LOGO.bmp", L"TITLE_LOGO");
	BmpManager->AddBitMap(L"../MyResource/MENU/MENU.bmp", L"MENU");
	BmpManager->AddBitMap(L"../MyResource/TITLE/TITLE_UNDER.bmp", L"MENU_UNDER");

	CGameObject* pMenuText = CAbstractFactory<CMenuText>::CreateObj((float)BUFCX / 2.f, (float)BUFCY / 9.f * 5.5f);
	dynamic_cast<CMenuText*>(pMenuText)->SetFrameKey(L"MENU");
	GameManager->AddObject(pMenuText, OBJ_UI);

	CGameObject* pMenuUnder = CAbstractFactory<CMenuUnder>::CreateObj((float)BUFCX / 2.f, (float)(BUFCY / 9.f * 6.8f));
	dynamic_cast<CMenuUnder*>(pMenuUnder)->SetFrameKey(L"MENU_UNDER");
	GameManager->AddObject(pMenuUnder, OBJ_UI);
}

void CMyMenu::Update()
{
	GameManager->Update();
}

void CMyMenu::LateUpdate()
{
	GameManager->LateUpdate();
}

void CMyMenu::Render(HDC hDC)
{
	DrawBackground(hDC, L"TITLE_LOGO");
	GameManager->Render(hDC);
}

void CMyMenu::Release()
{
	GameManager->ReleaseObj(OBJ_UI);
}
