#include "stdafx.h"
#include "Effect_Bullet_Collision.h"


CEffect_Bullet_Collision::CEffect_Bullet_Collision()
{
}


CEffect_Bullet_Collision::~CEffect_Bullet_Collision()
{
}

void CEffect_Bullet_Collision::Init()
{
}

void CEffect_Bullet_Collision::LateInit()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 70.f;
	m_bIsActive = true;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 40;
	m_LeftKey = L"E_NB_COLLISION_L";
	m_RightKey = L"E_NB_COLLISION_R";

	if (m_bIsLeft)
		m_pFrameKey = m_LeftKey;
	else
		m_pFrameKey = m_RightKey;
}

OBJECT_STATE CEffect_Bullet_Collision::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	return PLAY;
}

void CEffect_Bullet_Collision::LateUpdate()
{
	CGameObject::UpdateRect();
	FrameMove();
}

void CEffect_Bullet_Collision::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Bullet_Collision::Release()
{
}

void CEffect_Bullet_Collision::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = m_tFrame.iEnd;
		m_bIsActive = false;
	}
}
