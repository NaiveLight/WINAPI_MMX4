#include "stdafx.h"
#include "Door.h"


CDoor::CDoor()
{
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Init()
{
	m_tInfo.fCX = 320.f;
	m_tInfo.fCY = 240.f;
	m_iHitBoxCX = 30;
	m_iHitBoxCY = 72;

	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
	m_iCurHP = m_iMaxHP = 5;
	m_bIsDamaged = false;
}

void CDoor::LateInit()
{
}

OBJECT_STATE CDoor::Update()
{
	CGameObject::LateInit();
	return PLAY;
}

void CDoor::LateUpdate()
{
	UpdateRect();

	if (m_bIsDamaged)
		FrameMove();
}

void CDoor::Render(HDC hDC)
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();


	DrawObjectScroll(hDC, m_pFrameKey);
	Rectangle(hDC, m_tHitBoxRect.left - fScrollX, m_tHitBoxRect.top - fScrollY, m_tHitBoxRect.right - fScrollX, m_tHitBoxRect.bottom - fScrollY);
}

void CDoor::Release()
{
}

void CDoor::UpdateRect()
{
	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2) + 15;
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2) + 20;
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2) + 35;
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2) + 10;
}
