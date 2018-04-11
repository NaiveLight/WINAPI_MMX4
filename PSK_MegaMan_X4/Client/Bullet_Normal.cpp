#include "stdafx.h"
#include "Bullet_Normal.h"
#include "Player.h"
#include "Effect_Bullet_Collision.h"

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
	m_iHitBoxCX = 10;
	m_iHitBoxCY = 10;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 30;
	m_LeftKey = L"BULLET_NBL";
	m_RightKey = L"BULLET_NBR";
	m_fSpeedX = 8.f;
	m_iAttack = 1;
}

void CBullet_Normal::LateInit()
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
		fOffsetX = 20.f;
		fOffsetY = -10.f;
		break;

	case CPlayer::WALK_ATT: case CPlayer::WALK:
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

OBJECT_STATE CBullet_Normal::Update()
{
	CGameObject::LateInit();
	m_tInfo.fX += m_fSpeedX;

	if (abs(m_pTarget->GetInfo().fX - m_tInfo.fX) > 300)
		m_bIsActive = false;

	if (!m_bIsActive)
	{
		CGameObject* pEffect = CAbstractFactory<CEffect_Bullet_Collision>::CreateObj(m_tInfo.fX, m_tInfo.fY, L"E_BB_COLLISION_L", 3, 4, 0, 1);
		pEffect->SetIsLeft(m_bIsLeft);
		GameManager->AddObject(pEffect, OBJ_EFFECT);
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

void CBullet_Normal::CollisionCheck(OBJECT_ID eID)
{

}
