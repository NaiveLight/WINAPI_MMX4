#include "stdafx.h"
#include "MenuText.h"


CMenuText::CMenuText()
{
}


CMenuText::~CMenuText()
{
	Release();
}

void CMenuText::Init()
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 150.f;
}

OBJECT_STATE CMenuText::Update()
{	
	return PLAY;
}

void CMenuText::LateUpdate()
{
	CGameObject::UpdateRect();

	if (KeyManager->KeyDown(VK_UP))
	{
		m_iDrawID--;
	}

	if (KeyManager->KeyDown(VK_DOWN))
	{
		m_iDrawID++;
	}

	if (KeyManager->KeyDown('c') ||
		KeyManager->KeyDown('C') ||
		KeyManager->KeyDown('v') ||
		KeyManager->KeyDown('V') ||
		KeyManager->KeyDown(VK_RETURN) ||
		KeyManager->KeyDown(VK_SPACE)
		)
	{
		switch (m_iDrawID)
		{
		case 0:
			SceneManager->ChangeScene(CSceneManager::PLAYERSELECT);
			return;
		}
	}

	if (m_iDrawID < 0)
		m_iDrawID += 3;
	if (m_iDrawID > 2)
		m_iDrawID -= 3;
}

void CMenuText::Render(HDC hDC)
{
	CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC, (int) m_tTexRect.left, (int) m_tTexRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		pBmp->GetMemDC(), m_iDrawID * pBmp->GetBmpCX() / 3, 0, pBmp->GetBmpCX() / 3, pBmp->GetBmpCY(), RGB(255, 0, 255));
}

void CMenuText::Release()
{
}
