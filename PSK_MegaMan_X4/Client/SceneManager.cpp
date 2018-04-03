#include "stdafx.h"
#include "SceneManager.h"
#include "Title.h"
#include "MyMenu.h"
#include "PlayerSelect.h"
#include "Lobby.h"
#include "Stage1_1.h"

CSceneManager::CSceneManager()
	:m_pCurScene(nullptr), m_eCurScene(SCENE_END), m_ePrevScene(SCENE_END), m_bIsFade(false), m_btAlpha(0)
{
}


CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::LateInit()
{
}

void CSceneManager::Update()
{
	if (!m_bIsFade)
		m_pCurScene->Update();
	else
		FadeIn();
}

void CSceneManager::LateUpdate()
{
	m_pCurScene->LateUpdate();
}

void CSceneManager::Render(HDC hDC)
{
	m_pCurScene->Render(hDC);
	DrawAlphaColor(hDC, m_btAlpha);
}

void CSceneManager::Release()
{
	SafeDelete<CScene*>(m_pCurScene);
}

bool CSceneManager::FadeIn()
{
	if (m_btAlpha >= 10)
		m_btAlpha -= 6;
	else
	{
		m_btAlpha = 0;
		m_bIsFade = false;
		return true;
	}

	return false;
}

bool CSceneManager::FadeOut()
{
	if (m_btAlpha < 245)
		m_btAlpha += 6;
	else
	{
		m_btAlpha = 255;
		m_bIsFade = true;
		return true;
	}

	return false;
}

void CSceneManager::DrawAlphaColor(HDC hDC, int Alpha)
{
	CMyBmp* pBmp = BmpManager->FindImage(L"BG_BLACK");

	BLENDFUNCTION bf = { 0, 0, Alpha, 0 };

	GdiAlphaBlend(hDC, 0, 0, WINCX, WINCY, pBmp->GetMemDC(), 0, 0, WINCX, WINCY, bf);
}

void CSceneManager::ChangeScene(SCENEID eSceneID)
{
	m_eCurScene = eSceneID;

	if (m_eCurScene != m_ePrevScene)
	{
		SafeDelete<CScene*>(m_pCurScene);

		switch (m_eCurScene)
		{
		case TITLE:
			m_pCurScene = new CTitle;
			break;

		case MENU:
			m_pCurScene = new CMyMenu;
			break;

		case PLAYERSELECT:
			m_pCurScene = new CPlayerSelect;
			break;

		case LOBBY:
			m_pCurScene = new CLobby;
			break;

		case STAGE1_1:
			m_pCurScene = new CStage1_1;
			break;
		}

		m_pCurScene->Init();
		m_ePrevScene = m_eCurScene;
	}
}