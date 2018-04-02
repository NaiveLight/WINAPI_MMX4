#include "stdafx.h"
#include "Bullet_Normal.h"
#include "Player.h"

CBullet_Normal::CBullet_Normal()
{
}

CBullet_Normal::~CBullet_Normal()
{
	Release();
}

void CBullet_Normal::Init()
{
	m_bIsActive = true;
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_iHitBoxCX = 10.f;
	m_iHitBoxCY = 10.f;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
	m_LeftKey = L"BULLET_NBL";
	m_RightKey = L"BULLET_NBR";
	m_fSpeedX = 8.f;
}

void CBullet_Normal::LateInit()
{
	float fPlayerX = m_pTarget->GetInfo().fX;
	float fPlayerY = m_pTarget->GetInfo().fY;
	float fOffsetX = 0.f;
	float fOffsetY = 0.f;
	CPlayer::STANCE eStance = dynamic_cast<CPlayer*>(m_pTarget)->GetStance();
	m_bIsLeft = m_pTarget->GetIsLeft();

	switch (eStance)
	{
	case CPlayer::ATTACK_NORMAL:
		fOffsetX = 15.f;
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
		fOffsetX = 15.f;
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
		m_fSpeedX *= -1.f;
	}
	else
		m_pFrameKey = m_RightKey;

	m_tInfo.fX = fPlayerX + fOffsetX;
	m_tInfo.fY = fPlayerY + fOffsetY;
}

OBJECT_STATE CBullet_Normal::Update()
{
	CGameObject::LateInit();
	m_tInfo.fX += m_fSpeedX;

	if (abs(m_pTarget->GetInfo().fX - m_tInfo.fX) > 300)
		m_bIsActive = false;

	if (!m_bIsActive)
	{
		// effect2 Create
		return DESTROY;
	}
	return PLAY;
}

void CBullet_Normal::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CBullet_Normal::Render(HDC hDC)
{
	//DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CBullet_Normal::Release()
{
}

void CBullet_Normal::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (m_tFrame.iStart == m_tFrame.iEnd - 1)
			return;

		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = 0;
		m_bIsActive = false;
	}
}
