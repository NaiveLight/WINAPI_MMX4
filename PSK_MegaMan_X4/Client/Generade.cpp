#include "stdafx.h"
#include "Generade.h"
#include "Effect_Explosion.h"

CGenerade::CGenerade()
{
}

CGenerade::~CGenerade()
{
	Release();
}

void CGenerade::Init()
{
	m_tInfo.fCX = 25.f;
	m_tInfo.fCY = 25.f;
	m_iHitBoxCX = 15;
	m_iHitBoxCY = 15;
	m_pFrameKey = L"M_GENERADE";
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_fVelocityY = -3.f;
	m_bIsActive = true;
}

void CGenerade::LateInit()
{
	m_fVelocityX = m_bIsLeft ? -2.5f : 2.5f;
}

OBJECT_STATE CGenerade::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
	{
		GameManager->AddObject(
			CAbstractFactory<CEffect_Explosion>::CreateObj(m_tInfo.fX, m_tInfo.fY, L"E_EXPLOSION", 17, 18, 0, 1),
			OBJ_EFFECT);
		return DESTROY;
	}

	if (m_tInfo.fY >= 190)
	{
		CreateHitBox();

		m_bIsActive = false;
		return PLAY;
	}

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY += m_fVelocityY;
	m_fVelocityY += 0.25f;
	return PLAY;
}

void CGenerade::LateUpdate()
{
	UpdateRect();
}

void CGenerade::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CGenerade::Release()
{
}

void CGenerade::CreateHitBox()
{
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;
	UpdateRect();
}
