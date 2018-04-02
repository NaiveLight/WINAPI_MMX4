#include "stdafx.h"
#include "Effect_NB_Fire.h"
#include "Player.h"


CEffect_NB_Fire::CEffect_NB_Fire()
{
}


CEffect_NB_Fire::~CEffect_NB_Fire()
{
	Release();
}

void CEffect_NB_Fire::Init()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 18.f;
	m_bIsActive = true;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 20;
	m_LeftKey = L"E_NB_FIRE_L";
	m_RightKey = L"E_NB_FIRE_R";
}

void CEffect_NB_Fire::LateInit()
{

}

OBJECT_STATE CEffect_NB_Fire::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	float fPlayerX = m_pTarget->GetInfo().fX;
	float fPlayerY = m_pTarget->GetInfo().fY;
	float fOffsetX = 0.f;
	float fOffsetY = 0.f;
	CPlayer::STANCE eStance = dynamic_cast<CPlayer*>(m_pTarget)->GetStance();
	m_bIsLeft = m_pTarget->GetIsLeft();

	switch (eStance)
	{
	case CPlayer::ATTACK_NORMAL:
		fOffsetX = 20.f;
		fOffsetY = -10.f;
		break;

	case CPlayer::WALK_ATT:
		fOffsetX = 28.f;
		fOffsetY = -10.f;
		break;

	case CPlayer::DASH_ATT:
		fOffsetX = 34.f;
		fOffsetY = -2.f;
		break;

	case CPlayer::JUMP_ATT:
		fOffsetX = 20.f;
		fOffsetY = -11.f;
		break;

	case CPlayer::WALL_ATT:
		break;

	case CPlayer::WALL_JUMP_ATTACK:
		break;
	}

	if (m_bIsLeft)
	{
		m_pFrameKey = m_LeftKey;
		fOffsetX *= -1.f;
	}
	else
		m_pFrameKey = m_RightKey;

	m_tInfo.fX = fPlayerX + fOffsetX;
	m_tInfo.fY = fPlayerY + fOffsetY;
	return PLAY;
}

void CEffect_NB_Fire::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CEffect_NB_Fire::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_NB_Fire::Release()
{
}

void CEffect_NB_Fire::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = 0;
		m_bIsActive = false;
	}
}
