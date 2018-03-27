#pragma once
#include "Scene.h"
class CLobby :
	public CScene
{
public:
	CLobby();
	virtual ~CLobby();

	// CScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

