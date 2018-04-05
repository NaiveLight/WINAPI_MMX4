#include "stdafx.h"
#include "DamagedHP.h"
#include "Player.h"

CDamagedHP::CDamagedHP()
{
}


CDamagedHP::~CDamagedHP()
{
	Release();
}

void CDamagedHP::Init()
{
	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 32.f;
	m_iSrcHp = dynamic_cast<CPlayer*>(m_pTarget)->GetCurHp();
}

void CDamagedHP::LateInit()
{
}

OBJECT_STATE CDamagedHP::Update()
{
	m_iDestHp = dynamic_cast<CPlayer*>(m_pTarget)->GetCurHp();

	return PLAY;
}

void CDamagedHP::LateUpdate()
{
	UpdateRect();
}

void CDamagedHP::Render(HDC hDC)
{
}

void CDamagedHP::Release()
{
}
