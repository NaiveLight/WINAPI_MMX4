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
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 50;
	m_LeftKey = L"M_SPIKE_L";
	m_RightKey = L"M_SPIKE_R";
	m_pFrameKey = m_LeftKey;
	m_eCurStance = IDLE;
	m_fVelocityX = 1.0f;
}

void CSpikeMarl::LateInit()
{

}

OBJECT_STATE CSpikeMarl::Update()
{
	if (!m_bIsActive)
		return WAIT;

	if (m_fTragetDist <= 0.f)
		m_bIsLeft = true;
	else
		m_bIsLeft = false;

	if (abs(m_fTragetDist) <= 150 && m_eCurStance != ATTACK)
	{
		m_eCurStance = ATTACK_BEGINE;
		m_fVelocityX = 0.f;
	}
	else if (abs(m_fTragetDist) > 200)
	{

	}

	return PLAY;
}

void CSpikeMarl::LateUpdate()
{
	m_fTragetDist = m_pTarget->GetInfo().fX - m_tInfo.fX;

	if (!m_bIsActive)
	{
		// 타겟과의 거리가 300 이하면 활성화
		if (abs(m_fTragetDist) <= 300)
		{
			m_bIsActive = true;
		}
		return;
	}

	CGameObject::UpdateRect();
	FrameMove();
	SceneChange();
}

void CSpikeMarl::Render(HDC hDC)
{
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
		////switch(m_e)
		//case IDLE:

		//	break;
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
			m_tFrame.iEnd = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
			break;
		case ATTACK_BEGINE:
			m_tFrame.iScene = 1;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case ATTACK:
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
			m_tFrame.dwSpeed = 80;
			break;
		case TURN:
			m_tFrame.iScene = 4;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		}
	}
}
