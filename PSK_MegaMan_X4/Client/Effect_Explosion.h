#pragma once
#include "GameObject.h"
class CEffect_Explosion :
	public CGameObject
{
public:
	CEffect_Explosion();
	virtual ~CEffect_Explosion();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	//virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();
};

