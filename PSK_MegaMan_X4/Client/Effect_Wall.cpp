#include "stdafx.h"
#include "Effect_Wall.h"
#include "Player.h"

CEffect_Wall::CEffect_Wall()
{
}


CEffect_Wall::~CEffect_Wall()
{
	Release();
}

void CEffect_Wall::Init()
{
	m_LeftKey = L"E_WALL_L";
	m_RightKey = L"E_WALL_R";
}

void CEffect_Wall::LateInit()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 30.f;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 10;
	m_bIsActive = true;

	float offsetX = 12.f;
	float offsetY = 20.f;

	if (m_bIsLeft)
	{
		offsetX *= -1.f;
		m_pFrameKey = m_LeftKey;
	}
	else
		m_pFrameKey = m_RightKey;

	m_tInfo.fX = m_pTarget->GetInfo().fX + offsetX;
	m_tInfo.fY = m_pTarget->GetInfo().fY + offsetY;
}

OBJECT_STATE CEffect_Wall::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
	{
		dynamic_cast<CPlayer*>(m_pTarget)->SetWallEffecCreate(false);
		return DESTROY;
	}

	return PLAY;
}

void CEffect_Wall::LateUpdate()
{
	UpdateRect();
	FrameMove();
}

void CEffect_Wall::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEffect_Wall::Release()
{
}

void CEffect_Wall::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = m_tFrame.iEnd;
		m_bIsActive = false;
	}
}
