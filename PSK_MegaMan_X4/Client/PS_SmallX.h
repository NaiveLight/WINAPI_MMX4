#pragma once
#include "GameObject.h"
class CPS_SmallX :
	public CGameObject
{
private:
	CGameObject* m_pCursor;
	DWORD		m_dwAniTime;

public:
	CPS_SmallX();
	virtual ~CPS_SmallX();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetTargetX(CGameObject* pObj) { m_pCursor = pObj; }

private:
	void FrameMove() override;
};

