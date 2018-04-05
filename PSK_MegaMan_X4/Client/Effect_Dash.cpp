#include "stdafx.h"
#include "Effect_Dash.h"

CEffect_Dash::CEffect_Dash()
{
}


CEffect_Dash::~CEffect_Dash()
{
	Release();
}

void CEffect_Dash::Init()
{
	m_LeftKey = L"E_DASH_L";
	m_RightKey = L"E_DASH_R";

}

void CEffect_Dash::LateInit()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 50.f;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 20;
	m_bIsActive = true;
}

OBJECT_STATE CEffect_Dash::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
	{
		return DESTROY;
	}

	float offsetX = 40.f;

	if (!m_bIsLeft)
	{
		offsetX *= -1.f;
		m_pFrameKey = m_RightKey;
	}
	else
		m_pFrameKey = m_LeftKey;

	m_tInfo.fX = m_pTarget->GetInfo().fX + offsetX;
	m_tInfo.fY = m_pTarget->GetInfo().fY;
	return PLAY;
}

void CEffect_Dash::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CEffect_Dash::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Dash::Release()
{
}

void CEffect_Dash::FrameMove()
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
