#pragma once
#include "Scene.h"
class CLoading :
	public CScene
{
public:
	CLoading();
	virtual ~CLoading();

	// CScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

