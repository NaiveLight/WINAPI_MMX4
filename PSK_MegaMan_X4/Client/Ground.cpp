#include "stdafx.h"
#include "Ground.h"


CGround::CGround()
{
}

CGround::~CGround()
{
	Release();
}

void CGround::Init()
{
	m_bIsActive = true;
}

void CGround::LateInit()
{
}

OBJECT_STATE CGround::Update()
{
	CGameObject::LateInit();
	return PLAY;
}

void CGround::LateUpdate()
{
	//UpdateRect();
}

void CGround::Render(HDC hDC)
{
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();

	if (m_bIsLeft)
	{
		//Rectangle(hDC, m_tHitBoxRect.left - iScrollX, m_tHitBoxRect.top - iScrollY, m_tHitBoxRect.right - iScrollX, m_tHitBoxRect.bottom - iScrollY);
	}
	else
	{
		MoveToEx(hDC, m_ptLeftTop.x - iScrollX, m_ptLeftTop.y - iScrollY, nullptr);
		LineTo(hDC, m_ptRightBottom.x - iScrollX, m_ptRightBottom.y - iScrollY);
	}
}

void CGround::Release()
{
}
