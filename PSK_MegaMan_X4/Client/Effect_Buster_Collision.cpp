#include "stdafx.h"
#include "Effect_Buster_Collision.h"


CEffect_Buster_Collision::CEffect_Buster_Collision()
{
}


CEffect_Buster_Collision::~CEffect_Buster_Collision()
{
	Release();
}

void CEffect_Buster_Collision::Init()
{
}

void CEffect_Buster_Collision::LateInit()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_bIsActive = true;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 40;
	m_LeftKey = L"E_BB_COLLISION_L";
	m_RightKey = L"E_BB_COLLISION_R";

	if (m_bIsLeft)
		m_pFrameKey = m_LeftKey;
	else
		m_pFrameKey = m_RightKey;
}

OBJECT_STATE CEffect_Buster_Collision::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	return PLAY;
}

void CEffect_Buster_Collision::LateUpdate()
{
	CGameObject::UpdateRect();
	FrameMove();
}

void CEffect_Buster_Collision::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Buster_Collision::Release()
{
}

void CEffect_Buster_Collision::FrameMove()
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
