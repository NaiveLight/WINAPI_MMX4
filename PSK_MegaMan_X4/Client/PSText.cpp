#include "stdafx.h"
#include "PSText.h"


CPSText::CPSText()
{
}

CPSText::~CPSText()
{
	Release();
}

void CPSText::Init()
{
	m_tInfo.fCX = 500.f;
	m_tInfo.fCY = 50.f;
	m_fSpeed = 10.0f;
}

OBJECT_STATE CPSText::Update()
{
	if (m_bIsLeft)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else
	{
		m_tInfo.fX += m_fSpeed;
	}

	return PLAY;
}

void CPSText::LateUpdate()
{
	CGameObject::UpdateRect();
	if (m_bIsLeft)
	{
		if (m_tInfo.fX <= -350)
			m_tInfo.fX = m_fOriginX;
	}
	else
	{
		if (m_tTexRect.left >= BUFCX + 250)
			m_tInfo.fX = m_fOriginX;
	}
}

void CPSText::Render(HDC hDC)
{
	CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC, (int)m_tTexRect.left, (int)m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		pBmp->GetMemDC(), 0, 0, pBmp->GetBmpCX(), pBmp->GetBmpCY(), RGB(255, 0, 255));
}

void CPSText::Release()
{
}
