#include "stdafx.h"
#include "MapObj.h"


CMapObj::CMapObj()
	:m_tOriginInfo({})
{
}

CMapObj::~CMapObj()
{
	Release();
}

void CMapObj::Init()
{
	m_tInfo = m_tOriginInfo;
}

void CMapObj::LateInit()
{
	m_bIsActive = false;
}

OBJECT_STATE CMapObj::Update()
{
	CGameObject::LateInit();

	if (CheckScreen())
	{
		m_bIsActive = true;
	}
	else
	{
		Init();
	}


	if (m_bIsActive)
		return PLAY;
	else
		return WAIT;
}

void CMapObj::LateUpdate()
{
	if(m_bIsActive)
		UpdateRect();
}

void CMapObj::Render(HDC hDC)
{
	if(m_bIsActive)
		DrawObjectScroll(hDC, m_pFrameKey);
}

void CMapObj::Release()
{
}
