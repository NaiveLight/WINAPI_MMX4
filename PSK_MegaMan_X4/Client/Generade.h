#pragma once
#include "Actor.h"
class CGenerade :
	public CActor
{
public:
	CGenerade();
	virtual ~CGenerade();

	// CActor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void CreateHitBox();
};

