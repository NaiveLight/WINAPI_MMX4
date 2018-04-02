#include "stdafx.h"
#include "Effect_Charge.h"
#include "Player.h"

CEffect_Charge::CEffect_Charge()
{
}


CEffect_Charge::~CEffect_Charge()
{
	Release();
}

void CEffect_Charge::Init()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
}

void CEffect_Charge::LateInit()
{
}

OBJECT_STATE CEffect_Charge::Update()
{
	CGameObject::LateInit();

	m_bIsActive = dynamic_cast<CPlayer*>(m_pTarget)->GetIsCharge();

	if (!m_bIsActive)
	{
		return DESTROY;
	}

	m_tInfo.fX = m_pTarget->GetInfo().fX;
	m_tInfo.fY = m_pTarget->GetInfo().fY;
	return PLAY;
}

void CEffect_Charge::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CEffect_Charge::Render(HDC hDC)
{
	if(g_iFrame%4 >= 2)
		DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Charge::Release()
{
}
