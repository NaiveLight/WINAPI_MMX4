#include "stdafx.h"
#include "CurHP.h"


CCurHP::CCurHP()
{
}


CCurHP::~CCurHP()
{
}

void CCurHP::Init()
{
	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 32.f;
}

void CCurHP::LateInit()
{
}

OBJECT_STATE CCurHP::Update()
{
	return PLAY;
}

void CCurHP::LateUpdate()
{
	CGameObject::UpdateRect();
}

void CCurHP::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CCurHP::Release()
{
}
