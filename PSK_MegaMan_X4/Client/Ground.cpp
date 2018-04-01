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
}

void CGround::Render(HDC hDC)
{
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();

	if (m_bIsLeft)
	{
		Rectangle(hDC, m_tTexRect.left - iScrollX, m_tTexRect.top - iScrollY, m_tTexRect.right - iScrollX, m_tTexRect.bottom - iScrollY);
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
