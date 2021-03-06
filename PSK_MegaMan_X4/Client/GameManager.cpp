#include "stdafx.h"
#include "GameManager.h"
#include "GameObject.h"

CGameManager::CGameManager()
	:m_tScreenRect({}),
	m_fScrollX(0.f), m_fScrollY(0.f), 
	m_fMinScrollX(0.f), m_fMinScrollY(0.f),
	m_fMaxScrollX(0.f), m_fMaxScrollY(0.f),
	m_fShakePower(0.f), m_dwShakeTime(0),
	m_bIsShaking(false), m_bIsPaused(false), m_bDebugMode(false)
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

		//if (i == OBJ_EFFECT)
		//	cout << m_ObjectList[i].size();

		for (; iter_begin != iter_end;)
		{
			int iEvent = (*iter_begin)->Update();

			if (DESTROY == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else if (WAIT)
			{
				if (iter_begin == m_ObjectList[i].end())
					continue;
				else
					++iter_begin;
			}
			else
				++iter_begin;
		}
	}

	if (m_bIsShaking)
	{
		m_fShakePower *= -1.f;
		m_fScrollY += m_fShakePower;
		if (m_dwShakeTime < GetTickCount())
			CameraShakingEnd();
	}

	if (m_fScrollX < 0)
		m_fScrollX = 0;

	if (m_fScrollY < 0)
		m_fScrollY = 0;

	if (m_fScrollX > m_fMaxScrollX)
		m_fScrollX = m_fMaxScrollX;

	if (m_fScrollY > m_fMaxScrollY)
		m_fScrollY = m_fMaxScrollY;

	if (KeyManager->KeyDown('Q'))
		m_bHitboxDraw = !m_bHitboxDraw;
}

void CGameManager::LateUpdate()
{
	m_tScreenRect = { LONG(-50 - m_fScrollX), LONG(0 - m_fScrollY),
		LONG(BUFCX - m_fScrollX), LONG(BUFCY- m_fScrollY) };

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

	CCollision::BulletToObject(m_ObjectList[OBJ_BULLET], m_ObjectList[OBJ_MONSTER]);
	CCollision::BulletToObject(m_ObjectList[OBJ_BULLET], m_ObjectList[OBJ_BOSS]);
	CCollision::BulletToGround(m_ObjectList[OBJ_BULLET], m_ObjectList[OBJ_GROUND]);
}

void CGameManager::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; ++iter_begin)
		{
			if (m_bHitboxDraw)
				(*iter_begin)->DrawHitBox(hDC);

			(*iter_begin)->Render(hDC);
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

void CGameManager::SetScrollX(float fX)
{
	m_fScrollX += fX; 
	if (m_fMaxScrollX <= m_fScrollX) 
	{ 
		m_fScrollX = m_fMaxScrollX; 
	}
	if (m_fMinScrollX >= m_fScrollX)
	{
		m_fScrollX = m_fMinScrollX;
	}
}

void CGameManager::SetScrollY(float fY)
{
	m_fScrollY += fY; 
	if (m_fMaxScrollY <= m_fScrollY) 
	{ 
		m_fScrollY = m_fMaxScrollY; 
	}
	if (m_fMinScrollY >= m_fScrollY)
	{
		m_fScrollY = m_fMinScrollY;
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

void CGameManager::CameraShakingStart(float fPower)
{
	if (!m_bIsShaking)
	{
		//m_fPrevScrollX = m_fScrollX;
		m_fPrevScrollY = m_fScrollY;
		m_bIsShaking = true;
		m_fShakePower = fPower;
		m_dwShakeTime = GetTickCount() + 10000;
	}
}

void CGameManager::CameraShakingStart(float fPower, DWORD dwShakeEndTime)
{
	if (!m_bIsShaking)
	{
		m_fPrevScrollY = m_fScrollY;
		m_bIsShaking = true;
		m_fShakePower = fPower;
		m_dwShakeTime = GetTickCount() + dwShakeEndTime;
	}
}

void CGameManager::CameraShakingEnd()
{
	m_bIsShaking = false;
	m_fShakePower = 0.f;
	m_fScrollY = m_fPrevScrollY;
}
