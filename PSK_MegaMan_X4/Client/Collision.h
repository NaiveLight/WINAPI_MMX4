#pragma once

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool Screen(RECT& tScreen, CGameObject* pObj);
	static bool Ground(CGameObject* pPlayer, OBJLIST& srcList);
};

