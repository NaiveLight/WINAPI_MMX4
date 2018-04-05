#include "stdafx.h"
#include "PlayerHPBar.h"
#include "Player.h"
#include "CurHP.h"


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

	CGameObject* pCurHP = CAbstractFactory<CCurHP>::CreateObj(m_tInfo.fX - 11, m_tInfo.fY + 7, L"PLAYER_CUR_HP", 1, 2, 0, 1);
	pCurHP->SetTarget(GameManager->GetPlayer());
	GameManager->AddObject(pCurHP, OBJ_UI);
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

	if (m_tFrame.iStart < 0)
		m_tFrame.iStart += m_tFrame.iEnd;

	if (m_tFrame.iStart > m_tFrame.iEnd)
		m_tFrame.iStart -= m_tFrame.iEnd;

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
