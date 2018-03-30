#include "stdafx.h"
#include "LB_X.h"


CLB_X::CLB_X()
	:m_ePrevStance(END), m_eCurStance(END), m_bIsPlayed(false), m_dwStop(0)
{
}

CLB_X::~CLB_X()
{
	Release();
}

void CLB_X::Init()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	
	m_eCurStance = m_ePrevStance = IDLE;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iScene = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 100;
}

void CLB_X::LateInit()
{
	
}

OBJECT_STATE CLB_X::Update()
{
	CGameObject::LateInit();

	return PLAY;
}

void CLB_X::LateUpdate()
{
	UpdateRect();

	if (m_ePrevStance == TALK && m_tFrame.iStart == m_tFrame.iEnd)
	{
		m_eCurStance = RUNOUT;
	}

	if (m_eCurStance == RUNOUT && m_tFrame.iStart == m_tFrame.iEnd)
	{
		if(m_dwStop == 0)
			m_dwStop = GetTickCount();

		if (m_dwStop + 500 < GetTickCount())
			SceneManager->ChangeScene(CSceneManager::STAGE1_1);
	}

	if(!m_bIsPlayed)
		FrameMove();
	
	SceneChange();
}

void CLB_X::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CLB_X::Release()
{
}

void CLB_X::FrameMove()
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
		case IDLE: case TALK: case ANGRY:
			m_tFrame.iStart = 0;
			break;

		case RUNOUT:
			m_tFrame.iStart = 1;
			break;
		}
		m_bIsPlayed = true;
	}
}

void CLB_X::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			break;

		case TALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.iScene = 0;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUNOUT:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iScene = 1;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ANGRY:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 2;
			m_tFrame.iScene = 2;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePrevStance = m_eCurStance;
		m_bIsPlayed = false;
	}
}
