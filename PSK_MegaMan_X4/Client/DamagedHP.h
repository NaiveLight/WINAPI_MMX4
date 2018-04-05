#pragma once
#include "GameObject.h"
class CDamagedHP :
	public CGameObject
{
public:
	CDamagedHP();
	virtual ~CDamagedHP();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int m_iMaxHp;
	int m_iSrcHp;
	int m_iDestHp;
};

