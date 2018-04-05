#include "stdafx.h"
#include "Bullet_SemiBuster.h"
#include "Player.h"
#include "Effect_Bullet_Collision.h"

CBullet_SemiBuster::CBullet_SemiBuster()
{
}

CBullet_SemiBuster::~CBullet_SemiBuster()
{
	Release();
}

void CBullet_SemiBuster::Init()
{
	m_bIsActive = true;
	m_bIsActive = true;
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_iHitBoxCX = 20;
	m_iHitBoxCY = 20;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
	m_LeftKey = L"BULLET_BSL";
	m_RightKey = L"BULLET_BSR";
	m_fSpeedX = 8.f;
	m_iAttack = 2;
}

void CBullet_SemiBuster::LateInit()
{
	float fPlayerX = m_pTarget->GetInfo().fX;
	float fPlayerY = m_pTarget->GetInfo().fY;
	float fOffsetX = 0.f;
	float fOffsetY = 0.f;
	CPlayer::STANCE eStance = dynamic_cast<CPlayer*>(m_pTarget)->GetStance();
	m_bIsLeft = dynamic_cast<CPlayer*>(m_pTarget)->GetIsLeft();

	switch (eStance)
	{
	case CPlayer::ATTACK_NORMAL: case CPlayer::IDLE:
		fOffsetX = 15.f;
		fOffsetY = -10.f;
		break;

	case CPlayer::WALK_ATT: case CPlayer::WALK:
		fOffsetX = 28.f;
		fOffsetY = -10.f;
		break;

	case CPlayer::DASH_ATT: case CPlayer::DASH:
		fOffsetX = 34.f;
		fOffsetY = -2.f;
		break;

	case CPlayer::JUMP_ATT: case CPlayer::JUMP:
		fOffsetX = 15.f;
		fOffsetY = -11.f;
		break;

	case CPlayer::WALL_ATT:
		fOffsetX = -20.f;
		fOffsetY = -5.f;
		break;

	case CPlayer::WALL_JUMP_ATTACK:
		fOffsetX = -20.f;
		fOffsetY = -5.f;
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


	CPlayer::STANCE eCurStance = dynamic_cast<CPlayer*>(m_pTarget)->GetStance();

	if (eCurStance == CPlayer::WALL_ATT || eCurStance == CPlayer::WALL_JUMP_ATTACK)
	{
		if (m_pFrameKey == m_LeftKey)
			m_pFrameKey = m_RightKey;
		else
			m_pFrameKey = m_LeftKey;
	}

	m_tInfo.fX = fPlayerX + fOffsetX;
	m_tInfo.fY = fPlayerY + fOffsetY;
}

OBJECT_STATE CBullet_SemiBuster::Update()
{
	CGameObject::LateInit();
	m_tInfo.fX += m_fSpeedX;

	if (abs(m_pTarget->GetInfo().fX - m_tInfo.fX) > 200)
		m_bIsActive = false;

	if (!m_bIsActive)
	{
		// effect2 Create
		CGameObject* pEffect = CAbstractFactory<CEffect_Bullet_Collision>::CreateObj(m_tInfo.fX, m_tInfo.fY, L"E_BB_COLLISION_L", 3, 4, 0, 1);
		pEffect->SetIsLeft(m_bIsLeft);
		GameManager->AddObject(pEffect, OBJ_EFFECT);
		return DESTROY;
	}
	return PLAY;
}

void CBullet_SemiBuster::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CBullet_SemiBuster::Render(HDC hDC)
{
	//DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CBullet_SemiBuster::Release()
{
}

void CBullet_SemiBuster::FrameMove()
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
