#pragma once

class CCollision
{
public:
	CCollision();
	~CCollision();

public:
	static bool Screen(RECT& tScreen, CGameObject* pObj);
};

