#pragma once
#include "GameObject.h"
class CPS_X :
	public CGameObject
{
public:
	CPS_X();
	virtual ~CPS_X();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

