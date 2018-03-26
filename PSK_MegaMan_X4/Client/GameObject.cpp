#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	:m_tInfo({}), m_tTexRect({}), m_tHitBoxRect({}), m_iHitBoxCX(0), m_iHitBoxCY(0),
	m_tFrame({}), m_pFrameKey(nullptr), m_pTarget(nullptr),
	m_bIsInit(false), m_bIsActive(false), m_bIsLeft(false), 
	m_iAttack(0), m_fSpeed(0.f), m_iDrawID(0)
{
}


CGameObject::~CGameObject()
{
}

// ��� �ڽ�Ŭ������ Update���� LateInit�� �ѹ� �����ϰ� ��
// �������̵� �ʼ�.
void CGameObject::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

// ������Ʈ�� ��ġ�� ���� Rect ũ�� ����
void CGameObject::UpdateRect()
{
	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2);
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2);
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2);
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2);
}

//// ������Ʈ�� ��ġ�� ���� Rect ũ�� ����
//void CGameObject::UpdateRect(float fX, float fY)
//{
//}

// 1������ ���� �ִϸ��̼� ����
void CGameObject::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		m_tFrame.iStart = 0;
	}
}

// ������ Ű�� �ش��ϴ� �̹��� �׸���
void CGameObject::DrawObject(HDC hDC, const TCHAR * szName)
{
	//int iScrollX;
	//int iScrollY;

	//HDC hMemDC;

	//int iSizeX;
	//int iSizeY;

	//GdiTransparentBlt(hDC, m_tTexRect.left + iScrollX, m_tTexRect.top + iScrollY, iSizeX, iSizeY, hMemDC,
	//					m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
}

void CGameObject::DrawHitBox(HDC hDC)
{
}
