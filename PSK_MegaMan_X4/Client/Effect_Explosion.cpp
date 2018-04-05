#include "stdafx.h"
#include "Effect_Explosion.h"


CEffect_Explosion::CEffect_Explosion()
{
}

CEffect_Explosion::~CEffect_Explosion()
{
	Release();
}

void CEffect_Explosion::Init()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_bIsActive = true;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 40;
	m_pFrameKey = L"E_EXPLOSION";
}

OBJECT_STATE CEffect_Explosion::Update()
{
	if (!m_bIsActive)
		return DESTROY;

	return PLAY;
}

void CEffect_Explosion::LateUpdate()
{
	CGameObject::UpdateRect();
	FrameMove();
}

void CEffect_Explosion::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Explosion::Release()
{
}

void CEffect_Explosion::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		//if (m_tFrame.iStart == 0)
			//SoundManager->PlaySound(L"MMX49.wav", CSoundManager::EFFECT);

		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = m_tFrame.iEnd;
		m_bIsActive = false;
	}
}
