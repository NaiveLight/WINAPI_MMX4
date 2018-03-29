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
}

void CDoor::LateInit()
{
}

OBJECT_STATE CDoor::Update()
{
	LateInit();

	return OBJECT_STATE();
}

void CDoor::LateUpdate()
{
	UpdateRect();

	if (m_bIsDamaged)
		FrameMove();
}

void CDoor::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
	Rectangle(hDC, m_tHitBoxRect.left, m_tHitBoxRect.top, m_tHitBoxRect.right, m_tHitBoxRect.bottom);
}

void CDoor::Release()
{
}

void CDoor::UpdateRect()
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();

	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2) - fScrollX + 15;
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2) - fScrollY + 20;
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2) - fScrollX + 15;
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2) - fScrollY + 20;
}
