#pragma once
#include "GameObject.h"
class CMenuUnder :
	public CGameObject
{
private:
	DWORD m_dwOld;
	DWORD m_dwSpeed;

public:
	CMenuUnder();
	virtual ~CMenuUnder();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

