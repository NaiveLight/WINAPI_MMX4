#pragma once
#include "GameObject.h"
class CEffect_Charge_Body :
	public CGameObject
{
public:
	CEffect_Charge_Body();
	virtual ~CEffect_Charge_Body();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

