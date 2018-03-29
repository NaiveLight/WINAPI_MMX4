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
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 2.0f;
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
		if (m_tInfo.fX >= BUFCX + 350)
			m_tInfo.fX = m_fOriginX;
	}
}

void CPSText::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CPSText::Release()
{
}
