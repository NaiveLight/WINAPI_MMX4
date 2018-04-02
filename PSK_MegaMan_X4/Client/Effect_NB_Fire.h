#pragma once
#include "GameObject.h"
class CEffect_NB_Fire :
	public CGameObject
{
public:
	CEffect_NB_Fire();
	virtual ~CEffect_NB_Fire();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
};

