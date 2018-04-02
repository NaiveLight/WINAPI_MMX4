#pragma once
#include "GameObject.h"
class CCurHP :
	public CGameObject
{
public:
	CCurHP();
	virtual ~CCurHP();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

