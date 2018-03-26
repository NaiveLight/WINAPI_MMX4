#include "stdafx.h"
#include "SceneManager.h"
#include "Title.h"
#include "MyMenu.h"

CSceneManager::CSceneManager()
	:m_pCurScene(nullptr), m_eCurScene(SCENE_END), m_ePrevScene(SCENE_END), m_bIsFade(false), m_btAlpha(0)
{
}


CSceneManager::~CSceneManager()
{
	Release();
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
		switch (m_eCurScene)
		{
		case TITLE:
			break;

		case MENU:
			m_pCurScene = new CMyMenu;
			break;

		case PLAYERSELECT:
			break;

		case LOBBY:
			break;

		case STAGE:
			break;
		}

		m_ePrevScene = m_eCurScene;
	}

	m_pCurScene->Init();
}

void CSceneManager::RestartScene()
{
}
