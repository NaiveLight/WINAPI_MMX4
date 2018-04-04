#include "stdafx.h"
#include "Eregion.h"


CEregion::CEregion()
{
}

CEregion::~CEregion()
{
	Release();
}

void CEregion::Init()
{
	m_tInfo.fCX = 500.f;
	m_tInfo.fCY = 300.f;
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 70;

	m_LeftKey = L"B_EREGION_L";
	m_RightKey = L"B_EREGION_R";
	m_pFrameKey = m_RightKey;
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 250;
	m_fVelocityX = 1.0f;
	m_eCurStance = IDLE;
	m_iCurHP = m_iMaxHP = 20;
}

void CEregion::LateInit()
{
	m_bIsActive = true;
	m_bAttack = false;
}

OBJECT_STATE CEregion::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	//if (m_bAttack)
	//	return PLAY;

	//m_eCurStance = ATTACK_A;

	if (m_fTragetDist <= 0.f)
	{
		m_bIsLeft = true;
		m_pFrameKey = m_LeftKey;
	}
	else if (m_fTragetDist > 0.f)
	{
		m_bIsLeft = false;
		m_pFrameKey = m_RightKey;
	}

	return PLAY;
}

void CEregion::LateUpdate()
{
	UpdateRect();

	m_fTragetDist = m_pTarget->GetInfo().fX - m_tInfo.fX;

	FrameMove();
	SceneChange();
}

void CEregion::Render(HDC hDC)
{
	DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEregion::Release()
{
}

void CEregion::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;

		switch (m_eCurStance)
		{
		case ATTACK_A:
			if (m_tFrame.iStart == 6)
			{
				m_tFrame.dwSpeed = 2000;
				CreateHitBox();
			}
			break;
		case ATTACK_B:
			if (m_tFrame.iStart == m_tFrame.iEnd-1)
			{
				m_tFrame.dwSpeed = 3000;
			}
			break;
		}
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			break;
		case ATTACK_A:
			m_tFrame.iStart = 0;
			m_tFrame.dwSpeed = 150;
			ResetHitBox();
			//m_tFrame.iStart = m_tFrame.iEnd;
			//m_eCurStance = IDLE;
			//m_bAttack = false;
			break;
		case ATTACK_B:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			m_bAttack = false;
			break;
		}
	}
}

void CEregion::UpdateRect()
{
	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);
}

void CEregion::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iScene = 0;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case ATTACK_A:
			m_bAttack = true;
			m_tFrame.iScene = 1;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
			break;
		case ATTACK_B:
			m_bAttack = true;
			m_tFrame.iScene = 2;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;

		}
		m_ePrevStance = m_eCurStance;
	}
}

void CEregion::CreateHitBox()
{
	if (!m_bIsLeft)
	{
		m_tHitBoxRect.right = m_tInfo.fX - 30;
		m_tHitBoxRect.left = m_tHitBoxRect.right - 50;
	}
	else
	{
		m_tHitBoxRect.left = m_tInfo.fX + 30;
		m_tHitBoxRect.right = m_tHitBoxRect.left + 50;
	}

	m_tHitBoxRect.top = m_tInfo.fY + 30;
	m_tHitBoxRect.bottom = m_tHitBoxRect.top + 70;
}

void CEregion::ResetHitBox()
{
	m_tHitBoxRect = {};
}
