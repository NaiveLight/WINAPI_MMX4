#pragma once
#include "Actor.h"
class CDoor :
	public CActor
{
public:
	CDoor();
	virtual ~CDoor();

public:
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void UpdateRect();
	virtual void FrameMove();

	void Dead();
};

