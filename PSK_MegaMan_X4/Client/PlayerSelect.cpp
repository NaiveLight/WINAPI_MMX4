#include "stdafx.h"
#include "PlayerSelect.h"
#include "PSText.h"
#include "PS_X.h"
#include "PS_Zero.h"
#include "PS_Cursor.h"


CPlayerSelect::CPlayerSelect()
	:m_pX(nullptr), m_bCreateCursor(false)
{
}


CPlayerSelect::~CPlayerSelect()
{
	Release();
}

void CPlayerSelect::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_PLAYERSELECT.bmp", L"BG_PLAYER_SELECT");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_TEXT.bmp", L"PS_TEXT");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_X.bmp", L"PS_X");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_ZERO.bmp", L"PS_ZERO");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_CURSOR.bmp", L"PS_CURSOR");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_X_ANI", L"PS_X_ANI");
}

void CPlayerSelect::LateInit()
{
	CGameObject* pPSText = CAbstractFactory<CPSText>::CreateObj(BUFCX + 700, BUFCY / 6 * 0.5f);
	dynamic_cast<CPSText*>(pPSText)->SetFrameKey(L"PS_TEXT");
	dynamic_cast<CPSText*>(pPSText)->SetOriginX();
	dynamic_cast<CPSText*>(pPSText)->SetIsLeft(true);
	GameManager->AddObject(pPSText, OBJ_UI);

	pPSText = CAbstractFactory<CPSText>::CreateObj(-600, BUFCY / 6 * 5.5f);
	dynamic_cast<CPSText*>(pPSText)->SetFrameKey(L"PS_TEXT");
	dynamic_cast<CPSText*>(pPSText)->SetOriginX();
	dynamic_cast<CPSText*>(pPSText)->SetIsLeft(false);
	GameManager->AddObject(pPSText, OBJ_UI);

	CGameObject* pPS_X = CAbstractFactory<CPS_X>::CreateObj(- 300, BUFCY / 8 * 4.2f);
	dynamic_cast<CPS_X*>(pPS_X)->SetFrameKey(L"PS_X");
	GameManager->AddObject(pPS_X, OBJ_UI);

	m_pX = pPS_X;

	CGameObject* pPS_Zero = CAbstractFactory<CPS_Zero>::CreateObj(BUFCX + 300, BUFCY / 8 * 4.2f);
	dynamic_cast<CPS_Zero*>(pPS_Zero)->SetFrameKey(L"PS_ZERO");
	GameManager->AddObject(pPS_Zero, OBJ_UI);

	//CGameObject* pPS_Cursor = CAbstractFactory<CPS_Cursor>::CreateObj(m_pX->GetInfo().fX, m_pX->GetInfo().fY);
	//dynamic_cast<CPS_Cursor*>(pPS_Cursor)->SetFrameKey(L"PS_CURSOR");
	//dynamic_cast<CPS_Cursor*>(pPS_Cursor)->SetTargetX(GameManager->GetTargetByFrameKey(L"PS_X", OBJ_UI));
	//dynamic_cast<CPS_Cursor*>(pPS_Cursor)->SetTargetZero(GameManager->GetTargetByFrameKey(L"PS_ZERO", OBJ_UI));
}

void CPlayerSelect::Update()
{
	CScene::LateInit();
	GameManager->Update();
}

void CPlayerSelect::LateUpdate()
{
	GameManager->LateUpdate();

	if (m_pX->GetSpeed() <= 0.f && !m_bCreateCursor)
	{
		CGameObject* pPS_Cursor = CAbstractFactory<CPS_Cursor>::CreateObj();
		dynamic_cast<CPS_Cursor*>(pPS_Cursor)->SetFrameKey(L"PS_CURSOR");
		dynamic_cast<CPS_Cursor*>(pPS_Cursor)->SetTargetX(GameManager->GetTargetByFrameKey(L"PS_X", OBJ_UI));
		dynamic_cast<CPS_Cursor*>(pPS_Cursor)->SetTargetZero(GameManager->GetTargetByFrameKey(L"PS_ZERO", OBJ_UI));
		GameManager->AddObject(pPS_Cursor, OBJ_UI);
		m_bCreateCursor = true;
	}
}

void CPlayerSelect::Render(HDC hDC)
{
	DrawBackground(hDC, L"BG_PLAYER_SELECT");
	GameManager->Render(hDC);
}

void CPlayerSelect::Release()
{
	GameManager->ReleaseObj(OBJ_UI);
}
