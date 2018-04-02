#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect()
{
}


CEffect::~CEffect()
{
	Release();
}

void CEffect::Init()
{
}

void CEffect::LateInit()
{
}

OBJECT_STATE CEffect::Update()
{
	return PLAY;
}

void CEffect::LateUpdate()
{
}

void CEffect::Render(HDC hDC)
{
}

void CEffect::Release()
{
}

void CEffect::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = 0;
		m_bIsActive = false;
	}
}
