#include "stdafx.h"
#include "Title.h"
#include "MenuUnder.h"

CTitle::CTitle()
	:m_bLoading(false)
{
}


CTitle::~CTitle()
{
	Release();
}

void CTitle::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE_LOGO.bmp", L"BG_TITLE_LOGO");
	BmpManager->AddBitMap(L"../MyResource/MENU/MENU.bmp", L"MENU");
	BmpManager->AddBitMap(L"../MyResource/TITLE/TITLE_UNDER.bmp", L"MENU_UNDER");
}

void CTitle::LateInit()
{
	CGameObject* pMenuUnder = CAbstractFactory<CMenuUnder>::CreateObj((float)BUFCX / 2.f, (float)(BUFCY / 5.f * 3.5f), L"MENU_UNDER");
	GameManager->AddObject(pMenuUnder, OBJ_UI);
	SoundManager->PlaySound(L"03_Title.mp3", CSoundManager::UI);
}

void CTitle::Update()
{
	CScene::LateInit();
	GameManager->Update();
}

void CTitle::LateUpdate()
{
	GameManager->LateUpdate();

	if (KeyManager->KeyDown(VK_RETURN))
	{
		SoundManager->StopAll();
		SceneManager->ChangeScene(CSceneManager::MENU);
	}
}

void CTitle::Render(HDC hDC)
{
	DrawBackground(hDC, L"BG_TITLE_LOGO");
	GameManager->Render(hDC);
}

void CTitle::Release()
{
	GameManager->ReleaseObj(OBJ_UI);
}

