#include "stdafx.h"
#include "BossHPBar.h"
#include "Eregion.h"
#include "BossHPBar.h"
#include "CurHP.h"
#include "Actor.h"

CBossHPBar::CBossHPBar()
{
}


CBossHPBar::~CBossHPBar()
{
	Release();
}

void CBossHPBar::Init()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 60.f;
	m_bIsActive = true;
}

void CBossHPBar::LateInit()
{
	UpdateRect();
	// 체력바 & 무기 & 라이프 세팅

	m_iCurHp = m_iMaxHp = dynamic_cast<CActor*>(m_pTarget)->GetMaxHp();


	//CGameObject* pCurHP = CAbstractFactory<CCurHP>::CreateObj(m_tInfo.fX - 11, m_tInfo.fY + 7, L"PLAYER_CUR_HP", 1, 2, 0, 1);
	//pCurHP->SetTarget(this);
	//GameManager->AddObject(pCurHP, OBJ_UI);
}

OBJECT_STATE CBossHPBar::Update()
{
	CGameObject::LateInit();

	if (m_pTarget == nullptr)
		m_bIsActive = false;

	if (m_pTarget != nullptr)
		m_iCurHp = dynamic_cast<CActor*>(m_pTarget)->GetCurHp();;


	if (!m_bIsActive)
		return DESTROY;



	return PLAY;
}

void CBossHPBar::LateUpdate()
{

}

void CBossHPBar::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CBossHPBar::Release()
{
}
