#include "stdafx.h"
#include "PS_X.h"


CPS_X::CPS_X()
{
}


CPS_X::~CPS_X()
{
	Release();
}

void CPS_X::Init()
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
	m_fSpeed = 10.f;
}

OBJECT_STATE CPS_X::Update()
{
	m_tInfo.fX += m_fSpeed;
	return PLAY;
}

void CPS_X::LateUpdate()
{
	CGameObject::UpdateRect();

	if (m_tInfo.fX >= m_tInfo.fCX / 2.f  - 10.f)
		m_fSpeed = 0.f;
}

void CPS_X::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
	//CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);
	//GdiTransparentBlt(hDC, (int)m_tTexRect.left, (int)m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//	pBmp->GetMemDC(), 0, 0, pBmp->GetBmpCX(), pBmp->GetBmpCY(), RGB(255, 0, 255));
}

void CPS_X::Release()
{
}
