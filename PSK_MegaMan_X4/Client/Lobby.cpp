#include "stdafx.h"
#include "Lobby.h"
#include "LB_X.h"
#include "LBText.h"


CLobby::CLobby()
	:m_pLobbyX(nullptr), m_pLBText(nullptr), m_bScrollStop(false)
{
}


CLobby::~CLobby()
{
	Release();
}

void CLobby::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_LOBBY.bmp", L"BG_LOBBY");
	BmpManager->AddBitMap(L"../MyResource/LOBBY/LOBBY_X.bmp", L"LOBBY_X");
	BmpManager->AddBitMap(L"../MyResource/LOBBY/LOBBY_TEXT.bmp", L"LOBBY_TEXT");
	GameManager->SetMaxScrollY(250.f);
}

void CLobby::LateInit()
{
	SoundManager->PlayBGM(L"05_Stage Select.mp3");

	float fMaxScrollX = GameManager->GetMaxScrollX();
	float fMaxScrollY = GameManager->GetMaxScrollY();
	m_pLobbyX = CAbstractFactory<CLB_X>::CreateObj(BUFCX/5, BUFCY+BUFCY/5*3.5f, L"LOBBY_X", 2, 6, 0, 3);
	GameManager->AddObject(m_pLobbyX, OBJ_UI);
}

void CLobby::Update()
{
	CScene::LateInit();

	//스크롤이 멈추었는지 확인
	if (GameManager->GetScrollY() != GameManager->GetMaxScrollY())
	{
		GameManager->SetScrollY(1.0f);
	}
	else
	{
		m_bScrollStop = true;
	}

	GameManager->Update();
}

void CLobby::LateUpdate()
{
	// 스크롤이 멈추면 대화창 생성해주어야 함
	if (m_bScrollStop && m_pLBText == nullptr)
	{
		m_pLBText = CAbstractFactory<CLBText>::CreateObj(BUFCX / 2,  BUFCY / 4, L"LOBBY_TEXT", 5, 6, 0, 1);
		GameManager->AddObject(m_pLBText, OBJ_UI);
	}

	// 대화창이 바뀌어야 하며 X가 애니메이션을 실행해야 함
	if (KeyManager->KeyDown('c') ||
		KeyManager->KeyDown('C') ||
		KeyManager->KeyDown('v') ||
		KeyManager->KeyDown('V') ||
		KeyManager->KeyDown(VK_RETURN) ||
		KeyManager->KeyDown(VK_SPACE)
		)
	{
		if (!m_bScrollStop)
		{
			GameManager->SetScrollY(GameManager->GetMaxScrollY() - GameManager->GetScrollY());
			return;
		}

		if (m_pLBText != nullptr)
		{
			dynamic_cast<CLBText*>(m_pLBText)->IncreaseFrameStart();
			int iTextFrame = dynamic_cast<CLBText*>(m_pLBText)->GetFrameStart();

			switch (iTextFrame)
			{
			case 0: case 1: case 2: case 3: case 4:
				dynamic_cast<CLB_X*>(m_pLobbyX)->SetStance(CLB_X::IDLE);
				break;
			case 5:
				dynamic_cast<CLB_X*>(m_pLobbyX)->SetStance(CLB_X::TALK);
				break;
			}
		}
	}

	GameManager->LateUpdate();
}

void CLobby::Render(HDC hDC)
{
	float fScrollY = GameManager->GetScrollY();

	DrawBackground(hDC, L"BG_LOBBY", 0, fScrollY);
	GameManager->Render(hDC);
}

void CLobby::Release()
{
	SoundManager->StopAll();
	GameManager->ReleaseObj(OBJ_UI);
	GameManager->ResetScroll();
}
