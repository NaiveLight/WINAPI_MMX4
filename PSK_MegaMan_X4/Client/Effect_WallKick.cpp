#include "stdafx.h"
#include "Effect_WallKick.h"


CEffect_WallKick::CEffect_WallKick()
{
}


CEffect_WallKick::~CEffect_WallKick()
{
}

void CEffect_WallKick::Init()
{

}


void CEffect_WallKick::LateInit()
{
	m_LeftKey = L"E_WALLKICK_L";
	m_RightKey = L"E_WALLKICK_R";

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_bIsActive = true;

	float offsetX = 25.f;
	float offsetY = 27.f;

	if (m_bIsLeft)
	{
		offsetX *= -1.f;
		m_pFrameKey = m_LeftKey;
	}
	else
		m_pFrameKey = m_RightKey;

	m_tInfo.fX = m_pTarget->GetInfo().fX + offsetX;
	m_tInfo.fY = m_pTarget->GetInfo().fY + offsetY;
}

OBJECT_STATE CEffect_WallKick::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	return PLAY;
}

void CEffect_WallKick::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CEffect_WallKick::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_WallKick::Release()
{
}

void CEffect_WallKick::FrameMove()
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
