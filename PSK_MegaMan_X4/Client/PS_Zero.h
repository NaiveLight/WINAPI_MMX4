#pragma once
#include "GameObject.h"
class CPS_Zero :
	public CGameObject
{
public:
	CPS_Zero();
	virtual ~CPS_Zero();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

