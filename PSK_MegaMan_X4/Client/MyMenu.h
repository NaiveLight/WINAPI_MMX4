#pragma once
#include "Scene.h"
class CMyMenu :
	public CScene
{
private:


public:
	CMyMenu();
	virtual ~CMyMenu();

	// CScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

