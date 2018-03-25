#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
{
}


CActor::~CActor()
{
}

void CActor::Init()
{
}

void CActor::LateInit()
{
}

OBJECT_STATE CActor::Update()
{
	CGameObject::LateInit();

	return OBJECT_STATE();
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
