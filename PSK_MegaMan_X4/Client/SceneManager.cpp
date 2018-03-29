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
	m_pCurScene->Update();
}

void CSceneManager::LateUpdate()
{
	m_pCurScene->LateUpdate();
}

void CSceneManager::Render(HDC hDC)
{
	if(!m_bIsFade)
		m_pCurScene->Render(hDC);
}

void CSceneManager::Release()
{
	SafeDelete<CScene*>(m_pCurScene);
}

void CSceneManager::FadeIn()
{
}

void CSceneManager::FadeOut()
{
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



void CSceneManager::RestartScene()
{
}
