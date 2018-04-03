#pragma once
#include "Actor.h"
class CSpikeMarl :
	public CActor
{
public:
	CSpikeMarl();
	virtual ~CSpikeMarl();

	// CActor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

