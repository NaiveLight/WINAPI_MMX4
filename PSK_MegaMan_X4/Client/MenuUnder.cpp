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
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 20.f;
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
	if (g_iFrame % 11 >= 5)
		return;

	DrawObject(hDC, m_pFrameKey);
}

void CMenuUnder::Release()
{
}
