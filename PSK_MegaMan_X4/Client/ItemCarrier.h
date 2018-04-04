#pragma once
#include "Actor.h"
class CItemCarrier :
	public CActor
{

public:
	enum STANCE {IDLE, MOVE, END};

public:
	CItemCarrier();
	virtual ~CItemCarrier();

	// CActor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();
	void SceneChange();

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
	STANCE m_eCurStance;
	STANCE m_ePrevStance;
	float m_fTragetDist;
	bool m_bAttack;
};

