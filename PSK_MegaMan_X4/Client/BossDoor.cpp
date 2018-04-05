#include "stdafx.h"
#include "BossDoor.h"


CBossDoor::CBossDoor()
{
}

CBossDoor::~CBossDoor()
{
	Release();
}

void CBossDoor::Init()
{
	m_tInfo.fCX = 320.f;
	m_tInfo.fCY = 240.f;
	m_iHitBoxCX = 30;
	m_iHitBoxCY = 72;

	m_tFrame.dwSpeed = 10;
	m_tFrame.dwTime = GetTickCount();
	m_iCurHP = m_iMaxHP = 5;
	m_bIsDamaged = false;
	m_bIsActive = true;
}

void CBossDoor::LateInit()
{
}

OBJECT_STATE CBossDoor::Update()
{
	return OBJECT_STATE();
}

void CBossDoor::LateUpdate()
{
}

void CBossDoor::Render(HDC hDC)
{
}

void CBossDoor::Release()
{
}

void CBossDoor::FrameMove()
{
}
