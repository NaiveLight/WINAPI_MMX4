#include "stdafx.h"
#include "Door.h"
#include "Effect_Explosion.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Init()
{
	m_tInfo.fCX = 320.f;
	m_tInfo.fCY = 240.f;
	m_iHitBoxCX = 30;
	m_iHitBoxCY = 72;

	m_tFrame.dwSpeed = 10;
	m_tFrame.dwTime = GetTickCount();
	m_iCurHP = m_iMaxHP = 5;
	m_bIsDamaged = false;
	m_bIsActive = true;
	m_bIsGround = false;
}

void CDoor::LateInit()
{
}

OBJECT_STATE CDoor::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
	{
		return DESTROY;
	}

	if (m_bIsDead)
	{
		//dead play
		Dead();
		return PLAY;
	}

	return PLAY;
}

void CDoor::LateUpdate()
{
	UpdateRect();

	if (m_bIsDamaged)
		FrameMove();
}

void CDoor::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CDoor::Release()
{
}

void CDoor::UpdateRect()
{
	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2) + 15;
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2) + 20;
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2) + 35;
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2) + 10;
}

void CDoor::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = 0;
		m_bIsDamaged = false;
	}
}

void CDoor::Dead()
{

	for (int i = 0; i < 5; i++)
	{
		float fx = (float)(rand()%41);
		float fy = (float)(rand()%41);

		int random = rand() % 2;
		if (random)
		{
			fx *= -1.f;
			fy *= -1.f;
		}

		GameManager->AddObject(
			CAbstractFactory<CEffect_Explosion>::CreateObj(m_tInfo.fX + fx, m_tInfo.fY + fy, L"E_EXPLOSION", 17, 18, 0, 1),
			OBJ_EFFECT);
	}

	m_bIsActive = false;

}
