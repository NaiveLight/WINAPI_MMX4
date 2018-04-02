#include "stdafx.h"
#include "Effect_Charge_Body.h"
#include "Player.h"

CEffect_Charge_Body::CEffect_Charge_Body()
{
}

CEffect_Charge_Body::~CEffect_Charge_Body()
{
	Release();
}

void CEffect_Charge_Body::Init()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
}

void CEffect_Charge_Body::LateInit()
{
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
}

OBJECT_STATE CEffect_Charge_Body::Update()
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

void CEffect_Charge_Body::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CEffect_Charge_Body::Render(HDC hDC)
{
	if (g_iFrame % 4 >= 2)
		DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Charge_Body::Release()
{
}
