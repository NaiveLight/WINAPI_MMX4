#pragma once
#include "GameObject.h"
class CCurHP :
	public CGameObject
{
public:
	CCurHP();
	virtual ~CCurHP();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
