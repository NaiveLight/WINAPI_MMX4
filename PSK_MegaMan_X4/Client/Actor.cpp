#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
	:m_iCurHP(0), m_iMaxHP(0), m_iAttack(0)
{
}

CActor::~CActor()
{
	Release();
}

void CActor::Init()
{
}

void CActor::LateInit()
{
}

OBJECT_STATE CActor::Update()
{
	return PLAY;
}

void CActor::LateUpdate()
{
}

void CActor::Render(HDC hDC)
{
}

void CActor::Release()
{
}

