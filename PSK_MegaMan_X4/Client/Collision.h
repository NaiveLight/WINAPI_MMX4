#pragma once

class CPlayer;
class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool Screen(RECT& tScreen, CGameObject* pObj);
	static bool PlayerToWall(CPlayer* pPlayer, OBJLIST& srcList);
	static bool PlayerToGround(CPlayer* pPlayer, OBJLIST& srcList);
};

