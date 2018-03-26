#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"

CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
	Release();
}

void CGameManager::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		if (m_bIsPaused)
		{

		}

		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			OBJECT_STATE eEvent = (*iter)->Update();

			switch (eEvent)
			{
			case PLAY:
				++iter;
				break;

			case WAIT:
				++iter;
				break;

			case DESTROY:
				SafeDelete<CGameObject*>(*iter);
				iter = m_ObjectList[i].erase(iter);
				break;
			}
		}
	}
}

void CGameManager::LateUpdate()
{
	m_tScreenRect = {};

	for (int i = 0; i < OBJ_END; ++i)
	{
		if (m_bIsPaused)
		{

		}

		for (auto& pObj : m_ObjectList[i])
		{
			pObj->LateUpdate();
		}
	}
}

void CGameManager::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjectList[i])
		{
			pObj->Render(hDC);
		}
	}
}

void CGameManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		std::for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}

void CGameManager::AddObject(CGameObject * pObj, OBJECT_ID eID)
{
	m_ObjectList[eID].push_back(pObj);
}

void CGameManager::ReleaseObj(OBJECT_ID eID)
{
	for_each(m_ObjectList[eID].begin(), m_ObjectList[eID].end(), SafeDelete<CGameObject*>);
	m_ObjectList[eID].clear();
}

void CGameManager::SetCameraShaking(bool bIsShaking)
{
}
