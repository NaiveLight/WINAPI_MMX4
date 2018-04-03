#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	virtual ~CTitle();

	// CScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool m_bLoading;
};

