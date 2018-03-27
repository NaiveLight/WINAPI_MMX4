#include "stdafx.h"
#include "MenuUnder.h"


CMenuUnder::CMenuUnder()
{
}


CMenuUnder::~CMenuUnder()
{
	Release();
}

void CMenuUnder::Init()
{
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 80.f;
	m_dwOld = GetTickCount();
	m_dwSpeed = 1000;
}

OBJECT_STATE CMenuUnder::Update()
{
	return PLAY;
}

void CMenuUnder::LateUpdate()
{
	CGameObject::UpdateRect();
}

void CMenuUnder::Render(HDC hDC)
{
	if (m_dwOld + m_dwSpeed < GetTickCount())
		return;
	else
		m_dwOld = GetTickCount();

	CMyBmp* pBmp = BmpManager->FindImage(L"MENU_UNDER");

	GdiTransparentBlt(hDC, (int)m_tTexRect.left, (int)m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		pBmp->GetMemDC(), 0, 0, pBmp->GetBmpCX(), pBmp->GetBmpCY(), RGB(255, 0, 255));
}

void CMenuUnder::Release()
{
}
