#include "stdafx.h"
#include "PlayerHPBar.h"
#include "Player.h"


CPlayerHPBar::CPlayerHPBar()
{
}

CPlayerHPBar::~CPlayerHPBar()
{
	Release();
}

void CPlayerHPBar::Init()
{
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 100;
}

void CPlayerHPBar::LateInit()
{
	UpdateRect();
	// 체력바 & 무기 & 라이프 세팅
	m_iLife = dynamic_cast<CPlayer*>(m_pTarget)->GetIsLeft();
	m_iCurHp = dynamic_cast<CPlayer*>(m_pTarget)->GetCurHp();
	m_iMaxHp= dynamic_cast<CPlayer*>(m_pTarget)->GetMaxHp();
}

OBJECT_STATE CPlayerHPBar::Update()
{
	CGameObject::LateInit();

	if (KeyManager->KeyDown('A'))
	{
		m_tFrame.iStart--;
	}

	if (KeyManager->KeyDown('S'))
	{
		m_tFrame.iStart++;
	}

	return PLAY;
}

void CPlayerHPBar::LateUpdate()
{
}

void CPlayerHPBar::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CPlayerHPBar::Release()
{
}
