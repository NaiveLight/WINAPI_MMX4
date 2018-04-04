#include "stdafx.h"
#include "KnotBeretA.h"


CKnotBeretA::CKnotBeretA()
	:m_eCurStance(END), m_ePrevStance(END), m_fTragetDist(0.f)
{
}

CKnotBeretA::~CKnotBeretA()
{
	Release();
}

void CKnotBeretA::Init()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_iHitBoxCX = 45;
	m_iHitBoxCY = 45;
	m_LeftKey = L"M_KNOT_BERET_A_L";
	m_RightKey = L"M_KNOT_BERET_A_R";
	m_pFrameKey = m_LeftKey;
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 6;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 250;
	m_fVelocityX = 1.0f;
	m_eCurStance = IDLE;
	m_iCurHP = m_iMaxHP = 2;
}

void CKnotBeretA::LateInit()
{
	m_bIsActive = true;
}

OBJECT_STATE CKnotBeretA::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	if (m_bAttack)
		return PLAY;

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


	if (abs(m_fTragetDist) <= 150 && m_eCurStance != ATTACK)
	{
		m_eCurStance = ATTACK;
		m_fVelocityX = 0.f;
	}

	return PLAY;
}

void CKnotBeretA::LateUpdate()
{
	CGameObject::UpdateRect();

	m_fTragetDist = m_pTarget->GetInfo().fX - m_tInfo.fX;

	FrameMove();
	SceneChange();
}

void CKnotBeretA::Render(HDC hDC)
{
	DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CKnotBeretA::Release()
{
}

void CKnotBeretA::FrameMove()
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
		case WALK:
			m_tFrame.iStart = 0;
			break;
		case ATTACK:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			m_bAttack = false;
			break;
		case DEATH:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			break;
		case TURN:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			break;
		}
	}
}

void CKnotBeretA::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iScene = 0;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case WALK:
			m_tFrame.iScene = 1;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case ATTACK:
			m_bAttack = true;
			m_tFrame.iScene = 2;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		case DEATH:
			m_tFrame.iScene = 3;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 300;
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
