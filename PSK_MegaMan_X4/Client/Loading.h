#pragma once
#include "Scene.h"
class CLoading :
	public CScene
{
public:
	CLoading();
	virtual ~CLoading();

	// CScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

