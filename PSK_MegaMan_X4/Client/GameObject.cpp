#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	:m_tInfo({}), m_tTexRect({}), m_tHitBoxRect({}), m_iHitBoxCX(0), m_iHitBoxCY(0),
	m_tFrame({}), m_pFrameKey(nullptr), m_pTarget(nullptr),
	m_bIsInit(false), m_bIsActive(false), m_bIsLeft(false), 
	m_iFrameCnt(1), m_iSceneCnt(1),  m_fSpeedX(0.f), m_fSpeedY(0.f)
{
}


CGameObject::~CGameObject()
{
}

// 모든 자식클래스의 Update에서 LateInit을 한번 실행하게 함
// 오버라이딩 필수.
void CGameObject::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

// 오브젝트의 위치에 따른 Rect 크기 변경
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

//// 오브젝트의 위치에 따른 Rect 크기 변경
//void CGameObject::UpdateRect(float fX, float fY)
//{
//}

// 1프레임 마다 애니메이션 갱신
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

// 프레임 키에 해당하는 이미지 그리기
void CGameObject::DrawObject(HDC hDC, const TCHAR * pFrameKey)
{
	CMyBmp* pBmp = BmpManager->FindImage(pFrameKey);

	int iSizeX = pBmp->GetBmpCX() / (m_iFrameCnt);
	int iSizeY = pBmp->GetBmpCY() / (m_iSceneCnt);

	GdiTransparentBlt(hDC, m_tTexRect.left, m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY, pBmp->GetMemDC(),
		m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
}


void CGameObject::DrawObjectScroll(HDC hDC, const TCHAR * pFrameKey)
{
	int iScrollX = (int) GameManager->GetScrollX();
	int iScrollY = (int) GameManager->GetScrollY();

	CMyBmp* pBmp = BmpManager->FindImage(pFrameKey);

	int iSizeX = pBmp->GetBmpCX() / (m_iFrameCnt);
	int iSizeY = pBmp->GetBmpCY() / (m_iSceneCnt);

	GdiTransparentBlt(hDC, m_tTexRect.left - iScrollX, m_tTexRect.top - iScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, pBmp->GetMemDC(),
						m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
}

void CGameObject::DrawObjectMaxScroll(HDC hDC, const TCHAR * pFrameKey)
{
	int iScrollX = (int)GameManager->GetMaxScrollX();
	int iScrollY = (int)GameManager->GetMaxScrollY();

	CMyBmp* pBmp = BmpManager->FindImage(pFrameKey);

	int iSizeX = pBmp->GetBmpCX() / (m_iFrameCnt);
	int iSizeY = pBmp->GetBmpCY() / (m_iSceneCnt);

	GdiTransparentBlt(hDC, m_tTexRect.left + iScrollX, m_tTexRect.top - iScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, pBmp->GetMemDC(),
		m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
}

void CGameObject::DrawAlphaScroll(HDC hDC, const TCHAR * pFrameKey, BYTE alpha)
{
	HDC temphDC = GetDC(g_hWnd);

	HDC hMemDC = CreateCompatibleDC(temphDC);
	ReleaseDC(g_hWnd, temphDC);

	CMyBmp* pBmp = BmpManager->FindImage(pFrameKey);

	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();
	int iSizeX = pBmp->GetBmpCX() / (m_iFrameCnt);
	int iSizeY = pBmp->GetBmpCY() / (m_iSceneCnt);

	GdiTransparentBlt(hMemDC, 0, 0, pBmp->GetBmpCX(), pBmp->GetBmpCY(), pBmp->GetMemDC(),
		0, 0, pBmp->GetBmpCX(), pBmp->GetBmpCY(), RGB(255, 0, 255));

	BLENDFUNCTION bf = { 0, 0, alpha, 0 };

	GdiAlphaBlend(hDC, m_tInfo.fX - iScrollX, m_tInfo.fX - iScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, bf);

	ReleaseDC(g_hWnd, hMemDC);
}

void CGameObject::DrawHitBox(HDC hDC)
{
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();
	Rectangle(hDC, m_tHitBoxRect.left - iScrollX, m_tHitBoxRect.top - iScrollY, m_tHitBoxRect.right - iScrollX, m_tHitBoxRect.bottom - iScrollY);
}

