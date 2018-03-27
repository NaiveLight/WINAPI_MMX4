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
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end;)
		{
			int iEvent = (*iter_begin)->Update();

			if (DESTROY == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}
}

void CGameManager::LateUpdate()
{
	m_tScreenRect = {};

	for (int i = 0; i < OBJ_END; ++i)
	{
		if (m_ObjectList[i].empty())
			continue;

		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; ++iter_begin)
		{
			(*iter_begin)->LateUpdate();

			if (m_ObjectList[i].empty())
				break;
		}
	}
}

void CGameManager::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; ++iter_begin)
			(*iter_begin)->Render(hDC);
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

CGameObject * CGameManager::GetTargetByFrameKey(const TCHAR * pFrameKey, OBJECT_ID eID)
{
	auto iter = find_if(m_ObjectList[eID].begin(), m_ObjectList[eID].end(),
		[&pFrameKey](auto& pObj)
	{
		return !lstrcmp(pFrameKey, pObj->GetFrameKey());
	});

	if (iter == m_ObjectList[eID].end())
		return nullptr;
	else
		return *iter;
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
