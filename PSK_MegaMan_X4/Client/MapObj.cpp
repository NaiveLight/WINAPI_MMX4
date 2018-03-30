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
	m_bIsActive = true;
	m_bIsUpdate = false;
}

OBJECT_STATE CMapObj::Update()
{
	CGameObject::LateInit();

	if (m_bIsActive)
		return PLAY;
	else
		return WAIT;
}

void CMapObj::LateUpdate()
{
	if (!m_bIsUpdate)
	{
		UpdateRect();
	}
		
}

void CMapObj::Render(HDC hDC)
{
	if(m_bIsActive)
		DrawObjectScroll(hDC, m_pFrameKey);
}

void CMapObj::Release()
{
}
