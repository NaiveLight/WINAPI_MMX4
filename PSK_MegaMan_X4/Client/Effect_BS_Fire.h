#pragma once
#include "GameObject.h"
class CEffect_BS_Fire :
	public CGameObject
{
public:
	CEffect_BS_Fire();
	virtual ~CEffect_BS_Fire();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

