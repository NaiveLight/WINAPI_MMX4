#pragma once
#include "GameObject.h"
class CMenuText :
	public CGameObject
{
public:
	CMenuText();
	virtual ~CMenuText();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

