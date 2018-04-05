#pragma once

class CPlayer;
class CBullet;
class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool Screen(RECT& tScreen, CGameObject* pObj);
	static bool PlayerToWall(CPlayer* pPlayer, OBJLIST& srcList);
	static bool PlayerToGround(CPlayer* pPlayer, OBJLIST& srcList);
	static void BulletToObject(OBJLIST& bulletList, OBJLIST& srcList);
	static void BulletToGround(OBJLIST& bulletList, OBJLIST& srcList);
	static bool PlayerToMonster(CPlayer* pPlayer, OBJLIST& srcList);
};

