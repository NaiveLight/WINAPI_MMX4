#pragma once
#include "GameObject.h"
class CEffect_WallKick :
	public CGameObject
{
public:
	CEffect_WallKick();
	virtual ~CEffect_WallKick();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void LateInit();
	virtual void FrameMove();

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
};

