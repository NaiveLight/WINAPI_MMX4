#include "stdafx.h"
#include "PS_SmallX.h"


CPS_SmallX::CPS_SmallX()
	:m_pCursor(nullptr)
{
}

CPS_SmallX::~CPS_SmallX()
{
	Release();
}

void CPS_SmallX::Init()
{
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 400.f;
}

void CPS_SmallX::LateInit()
{
	m_pCursor = GameManager->GetTargetByFrameKey(L"PS_CURSOR", OBJ_UI);
}

OBJECT_STATE CPS_SmallX::Update()
{
	CGameObject::LateInit();

	return PLAY;
}

void CPS_SmallX::LateUpdate()
{
	FrameMove();
	if (m_pCursor->GetIsActive())
	{
		SceneManager->ChangeScene(CSceneManager::LOBBY);
		return;
	}
}

void CPS_SmallX::Render(HDC hDC)
{
}

void CPS_SmallX::Release()
{
}

void CPS_SmallX::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (m_tFrame.iStart == m_tFrame.iEnd)
			return;

		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();
	}
}
