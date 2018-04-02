#pragma once
#include "GameObject.h"
class CEffect :
	public CGameObject
{
public:
	CEffect();
	virtual ~CEffect();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();
};

