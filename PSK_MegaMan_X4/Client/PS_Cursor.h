#pragma once
#include "GameObject.h"
class CPS_Cursor :
	public CGameObject
{
private:
	CGameObject* m_pX;
	CGameObject* m_pZero;
public:
	CPS_Cursor();
	virtual ~CPS_Cursor();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetTargetX(CGameObject* pObj) { m_pX = pObj; }
	void SetTargetZero(CGameObject* pObj) { m_pZero = pObj; }
};

