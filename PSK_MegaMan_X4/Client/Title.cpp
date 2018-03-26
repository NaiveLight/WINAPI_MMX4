#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
	Release();
}

void CTitle::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE.bmp", L"BG_TITLE");
	BmpManager->AddBitMap(L"../MyResource/BG/BG_TITLE_LOGO.bmp", L"TITLE_LOGO");
	BmpManager->AddBitMap(L"../MyResource/MENU/MENU.bmp", L"MENU");
}

void CTitle::Update()
{
}

void CTitle::LateUpdate()
{
}

void CTitle::Render(HDC hDC)
{
}

void CTitle::Release()
{
}
