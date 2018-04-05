#include "stdafx.h"
#include "SpikeMarl.h"
#include "Effect_Explosion.h"

CSpikeMarl::CSpikeMarl()
	:m_eCurStance(END), m_ePrevStance(END), m_fTargetDist(0.f)
{
}

CSpikeMarl::~CSpikeMarl()
{
	Release();
}

void CSpikeMarl::Init()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;
	m_iHitBoxCX = 40;
	m_iHitBoxCY = 40;
	m_LeftKey = L"M_SPIKE_L";
	m_RightKey = L"M_SPIKE_R";
	m_pFrameKey = m_LeftKey;
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 250;
	m_fVelocityX = 1.0f;
	m_eCurStance = IDLE;
	m_iCurHP = m_iMaxHP = 3;
	m_iAttack = 2;
}

void CSpikeMarl::LateInit()
{
	m_bIsActive = true;
}

OBJECT_STATE CSpikeMarl::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	if (m_bIsDead)
	{
		Dead();
		return PLAY;
	}

	if (m_eCurStance == ATTACK_BEGINE || m_eCurStance == ATTACK_AFTER)
		return PLAY;

	if (m_bAttack)
	{
		m_fSpeedX= m_bIsLeft ? -20.f : 20.f;
		return PLAY;
	}

	if (m_fTargetDist <= 0.f)
	{
		m_bIsLeft = true;
		m_pFrameKey = m_LeftKey;
	}
	else if(m_fTargetDist > 0.f)
	{
		m_bIsLeft = false;
		m_pFrameKey = m_RightKey;
	}
		
	if (100 <= abs(m_fTargetDist) && abs(m_fTargetDist) < 150)
	{
		m_eCurStance = IDLE;
		m_fVelocityX = m_bIsLeft ? -0.5f : 0.5f;
	}
	else if (abs(m_fTargetDist) < 100 && m_eCurStance != ATTACK)
	{
		m_eCurStance = ATTACK_BEGINE;
		m_fVelocityX = 0.f;
	}

	m_tInfo.fX += m_fVelocityX;

	return PLAY;
}

void CSpikeMarl::LateUpdate()
{

	CGameObject::UpdateRect();

	m_fTargetDist = m_pTarget->GetInfo().fX - m_tInfo.fX;
	
	FrameMove();
	SceneChange();
}

void CSpikeMarl::Render(HDC hDC)
{
	//DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CSpikeMarl::Release()
{
}

void CSpikeMarl::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (m_eCurStance == IDLE)
		{
			if (m_tFrame.iStart == 0)
				m_tFrame.dwSpeed = 500;
			else
				m_tFrame.dwSpeed = 250;
		}

		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_eCurStance == ATTACK)
		{
			m_fVelocityX = 0.5f;
			if (!m_bIsLeft)
				m_fVelocityX *= -1.f;

			m_tInfo.fX += m_fVelocityX + m_fSpeedX;
		}
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			break;
		case ATTACK_BEGINE:
			//m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = ATTACK;
			break;
		case ATTACK:
			//m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = ATTACK_AFTER;
			break;
		case ATTACK_AFTER:
			//m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			m_bAttack = false;
			break;
		case TURN:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			break;
		}
	}
}

void CSpikeMarl::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iScene = 0;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 250;
			break;
		case ATTACK_BEGINE:
			m_tFrame.iScene = 1;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 250;
			break;
		case ATTACK:
			m_bAttack = true;
			m_tFrame.iScene = 2;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 30;
			SoundManager->PlaySound(L"SPIKE_ATTACK.wav", CSoundManager::MONSTER);
			break;
		case ATTACK_AFTER:
			m_tFrame.iScene = 3;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 250;
			break;
		case TURN:
			m_tFrame.iScene = 4;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
			break;
		}
		m_ePrevStance = m_eCurStance;
	}
}

void CSpikeMarl::Dead()
{
	// 익스플로젼 이펙트 생성 및 Active false
	GameManager->AddObject(
		CAbstractFactory<CEffect_Explosion>::CreateObj(m_tInfo.fX, m_tInfo.fY, L"E_EXPLOSION", 17, 18, 0, 1),
		OBJ_EFFECT);
	m_bIsActive = false;
}
