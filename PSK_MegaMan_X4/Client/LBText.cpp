#include "stdafx.h"
#include "LBText.h"


CLBText::CLBText()
{
}


CLBText::~CLBText()
{
	Release();
}

void CLBText::Init()
{
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 100.f;
}

void CLBText::LateInit()
{
}

OBJECT_STATE CLBText::Update()
{
	return PLAY;
}

void CLBText::LateUpdate()
{
	UpdateRect();
}

void CLBText::Render(HDC hDC)
{
	DrawObject(hDC, m_pFrameKey);
}

void CLBText::Release()
{
}
