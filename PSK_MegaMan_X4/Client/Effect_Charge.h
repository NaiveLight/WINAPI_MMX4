#pragma once
#include "GameObject.h"
class CEffect_Charge :
	public CGameObject
{
public:
	CEffect_Charge();
	virtual ~CEffect_Charge();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

