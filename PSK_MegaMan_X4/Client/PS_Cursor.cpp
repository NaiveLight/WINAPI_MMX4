#include "stdafx.h"
#include "PS_Cursor.h"


CPS_Cursor::CPS_Cursor()
	:m_pX(nullptr), m_pZero(nullptr), m_bIsSeleted(false)
{
}


CPS_Cursor::~CPS_Cursor()
{
	Release();
}

void CPS_Cursor::Init()
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 180.f;
	m_tFrame.iScene = 1;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.dwSpeed = 20;
	m_tFrame.dwTime = GetTickCount();
}

void CPS_Cursor::LateInit()
{
	m_tInfo.fX = m_pX->GetInfo().fX + 5.f;
	m_tInfo.fY = m_pX->GetInfo().fY - 10.f;
}

OBJECT_STATE CPS_Cursor::Update()
{
	CGameObject::LateInit();

	return PLAY;
}

void CPS_Cursor::LateUpdate()
{
	if (KeyManager->KeyDown(VK_RIGHT))
	{
		m_tFrame.iScene = 0;
		m_tInfo.fX = m_pZero->GetInfo().fX;
		m_tInfo.fY = m_pZero->GetInfo().fY - 10.f;
		SoundManager->PlaySound(L"PS_CONTROL.wav", CSoundManager::UI);
	}

	if (KeyManager->KeyDown(VK_LEFT))
	{
		m_tFrame.iScene = 1;
		m_tInfo.fX = m_pX->GetInfo().fX +5.f;
		m_tInfo.fY = m_pX->GetInfo().fY - 10.f;
		SoundManager->PlaySound(L"PS_CONTROL.wav", CSoundManager::UI);
	}

	if (KeyManager->KeyDown('c') ||
		KeyManager->KeyDown('C') ||
		KeyManager->KeyDown('v') ||
		KeyManager->KeyDown('V') ||
		KeyManager->KeyDown(VK_RETURN) ||
		KeyManager->KeyDown(VK_SPACE)
		)
	{
		if (m_tFrame.iScene == 1)
		{
			m_bIsActive = true;
			SoundManager->PlaySound(L"PS_SELECT.wav", CSoundManager::UI);
			m_tFrame.dwTime = GetTickCount();
		}
	}

	UpdateRect();
	CGameObject::FrameMove();
}

void CPS_Cursor::Render(HDC hDC)
{
	CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC, (int)m_tTexRect.left, (int)m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		pBmp->GetMemDC(), m_tFrame.iStart * pBmp->GetBmpCX() / 3, m_tFrame.iScene * pBmp->GetBmpCY() / 2, pBmp->GetBmpCX()/ 3, pBmp->GetBmpCY() / 2, RGB(255, 0, 255));
}

void CPS_Cursor::Release()
{
}
