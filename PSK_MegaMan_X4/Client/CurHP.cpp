#include "stdafx.h"
#include "CurHP.h"
#include "Player.h"

CCurHP::CCurHP()
{
}


CCurHP::~CCurHP()
{
	Release();
}

void CCurHP::Init()
{
	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 33.5f;
}

void CCurHP::LateInit()
{
	m_iMaxHp = m_iSrcHp = m_iDestHp = dynamic_cast<CPlayer*>(m_pTarget)->GetCurHp();
}

OBJECT_STATE CCurHP::Update()
{
	CGameObject::LateInit();

	m_iDestHp = dynamic_cast<CPlayer*>(m_pTarget)->GetCurHp();

	float hpRatio = m_iDestHp / (float)m_iMaxHp;

	if (hpRatio <= 0.5f)
		m_tFrame.iStart = 1;
	else if (hpRatio >= 0.5f)
		m_tFrame.iStart = 0;

	return PLAY;
}

void CCurHP::LateUpdate()
{
	CCurHP::UpdateRect();
}

void CCurHP::Render(HDC hDC)
{
	CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);

	int iSizeX = pBmp->GetBmpCX() / (m_iFrameCnt);
	int iSizeY = pBmp->GetBmpCY() / (m_iSceneCnt);

	GdiTransparentBlt(hDC, m_tTexRect.left, m_tTexRect.top, (int)m_tInfo.fCX, (int)(m_tInfo.fCY * m_iDestHp / (float)m_iMaxHp), pBmp->GetMemDC(),
		m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
}

void CCurHP::Release()
{
}

void CCurHP::UpdateRect()
{
	// top이 바텀에서 hpRatio만큼 그려져야한다.
	// 바텀 - fcy * hp비율
	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);
	m_tTexRect.top = m_tTexRect.bottom - m_tInfo.fCY * (m_iDestHp / (float)m_iMaxHp);

}
