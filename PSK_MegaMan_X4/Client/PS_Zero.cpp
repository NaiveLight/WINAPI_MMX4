#include "stdafx.h"
#include "PS_Zero.h"


CPS_Zero::CPS_Zero()
{
}


CPS_Zero::~CPS_Zero()
{
	Release();
}

void CPS_Zero::Init()
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
	m_fMaxSpeed = -10.f;
}

OBJECT_STATE CPS_Zero::Update()
{
	m_tInfo.fX += m_fMaxSpeed;
	return PLAY;
}

void CPS_Zero::LateUpdate()
{
	CGameObject::UpdateRect();
	if (m_tInfo.fX <= BUFCX - m_tInfo.fCX/2)
		m_fMaxSpeed = 0.f;
}

void CPS_Zero::Render(HDC hDC)
{
	CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC, (int)m_tTexRect.left, (int)m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		pBmp->GetMemDC(), 0, 0, pBmp->GetBmpCX(), pBmp->GetBmpCY(), RGB(255, 0, 255));
}

void CPS_Zero::Release()
{
}
