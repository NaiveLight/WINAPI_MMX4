#include "stdafx.h"
#include "Lobby.h"


CLobby::CLobby()
{
}


CLobby::~CLobby()
{
	Release();
}

void CLobby::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_LOBBY.bmp", L"BG_LOBBY");
}

void CLobby::LateInit()
{
}

void CLobby::Update()
{
}

void CLobby::LateUpdate()
{
}

void CLobby::Render(HDC hDC)
{
	DrawBackground(hDC, L"BG_LOBBY");
}

void CLobby::Release()
{
}
