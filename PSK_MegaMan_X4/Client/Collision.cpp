#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"

CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

bool CCollision::Screen(RECT & tScreen, CGameObject * pObj)
{
	RECT rc = {};

	if (IntersectRect(&rc, &tScreen, &pObj->GetTexRect()))
		return true;

	return false;
}
