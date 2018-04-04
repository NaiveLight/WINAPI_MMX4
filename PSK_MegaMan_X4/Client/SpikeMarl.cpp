#include "stdafx.h"
#include "SpikeMarl.h"


CSpikeMarl::CSpikeMarl()
	:m_eCurStance(END), m_ePrevStance(END), m_fTragetDist(0.f)
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
	m_iCurHP = m_iMaxHP = 2;
}

void CSpikeMarl::LateInit()
{
	m_bIsActive = true;
}

OBJECT_STATE CSpikeMarl::Update()
{
	//if (!m_bIsActive)
	//	return WAIT;

	CGameObject::LateInit();


	if (m_bAttack)
		return PLAY;

	if (m_fTragetDist <= 0.f)
	{
		m_bIsLeft = true;
		m_pFrameKey = m_LeftKey;
	}
	else if(m_fTragetDist > 0.f)
	{
		m_bIsLeft = false;
		m_pFrameKey = m_RightKey;
	}
		

	if (abs(m_fTragetDist) <= 150 && m_eCurStance != ATTACK)
	{
		m_eCurStance = ATTACK_BEGINE;
		m_fVelocityX = 0.f;
	}

	return PLAY;
}

void CSpikeMarl::LateUpdate()
{

	CGameObject::UpdateRect();

	m_fTragetDist = m_pTarget->GetInfo().fX - m_tInfo.fX;
	
	FrameMove();
	SceneChange();
}

void CSpikeMarl::Render(HDC hDC)
{
	DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CSpikeMarl::Release()
{
}

void CSpikeMarl::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
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
			m_tFrame.dwSpeed = 150;
			break;
		case ATTACK:
			m_bAttack = true;
			m_tFrame.iScene = 2;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 80;
			break;
		case ATTACK_AFTER:
			m_tFrame.iScene = 3;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
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
