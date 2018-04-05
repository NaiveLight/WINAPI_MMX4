#pragma once
#include "GameObject.h"
class CEffect_Explosion :
	public CGameObject
{
public:
	CEffect_Explosion();
	virtual ~CEffect_Explosion();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	//virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();
};

