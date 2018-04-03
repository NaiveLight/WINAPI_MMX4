#include "stdafx.h"
#include "PlayerSelect.h"
#include "PSText.h"
#include "PS_X.h"
#include "PS_Zero.h"
#include "PS_Cursor.h"


CPlayerSelect::CPlayerSelect()
	:m_pX(nullptr), m_bCreateCursor(false), m_pCursor(nullptr)
{
}


CPlayerSelect::~CPlayerSelect()
{
	Release();
}

void CPlayerSelect::Init()
{
	m_bChanceScene = false;
	BmpManager->AddBitMap(L"../MyResource/BG/BG_PLAYERSELECT.bmp", L"BG_PLAYER_SELECT");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/포맷변환_PS_TEXT.bmp", L"PS_TEXT");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/포맷변환_PS_X.bmp", L"PS_X");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/포맷변환_PS_ZERO.bmp", L"PS_ZERO");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/포맷변환_PS_CURSOR.bmp", L"PS_CURSOR");
	BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_X_ANI", L"PS_X_ANI");
	SoundManager->PlayBGM(L"04_Player Select.mp3");
}

void CPlayerSelect::LateInit()
{
	CGameObject* pPSText = CAbstractFactory<CPSText>::CreateObj(BUFCX + 200, BUFCY / 6 * 0.5f, L"PS_TEXT");
	pPSText->SetIsLeft(true);
	dynamic_cast<CPSText*>(pPSText)->SetOriginX();
	GameManager->AddObject(pPSText, OBJ_UI);

	pPSText = CAbstractFactory<CPSText>::CreateObj(-200, BUFCY / 6 * 5.5f, L"PS_TEXT");
	pPSText->SetIsLeft(false);
	dynamic_cast<CPSText*>(pPSText)->SetOriginX();
	GameManager->AddObject(pPSText, OBJ_UI);

	CGameObject* pPS_X = CAbstractFactory<CPS_X>::CreateObj(- 300, BUFCY / 8 * 4.2f, L"PS_X");
	GameManager->AddObject(pPS_X, OBJ_UI);

	m_pX = pPS_X;

	CGameObject* pPS_Zero = CAbstractFactory<CPS_Zero>::CreateObj(BUFCX + 300, BUFCY / 8 * 4.2f, L"PS_ZERO");
	GameManager->AddObject(pPS_Zero, OBJ_UI);
}

void CPlayerSelect::Update()
{
	CScene::LateInit();

	if (!m_bCreateCursor && m_pX->GetSpeed() <= 0.f)
	{
		BmpManager->AddBitMap(L"../MyResource/PlayerSelect/PS_X_ANI", L"PS_X_ANI");

		m_pCursor = CAbstractFactory<CPS_Cursor>::CreateObj(-BUFCX, -BUFCY, L"PS_CURSOR", 2, 3, 1, 2);
		dynamic_cast<CPS_Cursor*>(m_pCursor)->SetTargetX(GameManager->GetTargetByFrameKey(L"PS_X", OBJ_UI));
		dynamic_cast<CPS_Cursor*>(m_pCursor)->SetTargetZero(GameManager->GetTargetByFrameKey(L"PS_ZERO", OBJ_UI));
		GameManager->AddObject(m_pCursor, OBJ_UI);
		m_bCreateCursor = true;
	}

	if(m_pCursor != nullptr)
		m_bChanceScene = m_pCursor->GetIsActive();

	GameManager->Update();

	if (m_bChanceScene)
	{
		if (SceneManager->FadeOut())
		{
			SceneManager->ChangeScene(CSceneManager::LOBBY);
		}
	}
}

void CPlayerSelect::LateUpdate()
{
	GameManager->LateUpdate();
}

void CPlayerSelect::Render(HDC hDC)
{
	DrawBackground(hDC, L"BG_PLAYER_SELECT");
	GameManager->Render(hDC);
}

void CPlayerSelect::Release()
{
	SoundManager->StopSound(CSoundManager::BGM);
	GameManager->ReleaseObj(OBJ_UI);
}
