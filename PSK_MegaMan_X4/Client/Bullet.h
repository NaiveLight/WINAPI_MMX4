#pragma once
#include "GameObject.h"
class CBullet :
	public CGameObject
{
public:
	CBullet();
	virtual ~CBullet();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	const int  GetAttack() { return m_iAttack; }

protected:
	int m_iAttack;
};

