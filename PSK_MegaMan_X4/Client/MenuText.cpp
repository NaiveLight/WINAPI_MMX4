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
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY =  50.f;
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
		m_tFrame.iStart--;
		SoundManager->PlaySound(L"MENU_CONTROL.wav", CSoundManager::UI);
	}

	if (KeyManager->KeyDown(VK_DOWN))
	{
		m_tFrame.iStart++;
		SoundManager->PlaySound(L"MENU_CONTROL.wav", CSoundManager::UI);
	}

	if (KeyManager->KeyDown('c') ||
		KeyManager->KeyDown('C') ||
		KeyManager->KeyDown('v') ||
		KeyManager->KeyDown('V') ||
		KeyManager->KeyDown(VK_RETURN) ||
		KeyManager->KeyDown(VK_SPACE)
		)
	{
		switch (m_tFrame.iStart)
		{
		case 0:
			SoundManager->PlaySound(L"MENU_SELECT.wav", CSoundManager::UI);
			SceneManager->ChangeScene(CSceneManager::PLAYERSELECT);
			return;
		}
	}

	if (m_tFrame.iStart < 0)
		m_tFrame.iStart += m_tFrame.iEnd + 1;
	if (m_tFrame.iStart > m_tFrame.iEnd)
		m_tFrame.iStart -= m_tFrame.iEnd + 1;
}

void CMenuText::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CMenuText::Release()
{
}
