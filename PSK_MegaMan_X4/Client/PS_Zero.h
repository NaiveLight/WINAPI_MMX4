#pragma once
#include "GameObject.h"
class CPS_Zero :
	public CGameObject
{
public:
	CPS_Zero();
	virtual ~CPS_Zero();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

