#pragma once
#include "Actor.h"
class CEregion :
	public CActor
{
public:
	enum STANCE {IDLE, ATTACK_A, ATTACK_B, END};

public:
	CEregion();
	virtual ~CEregion();

	// CActor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();
	virtual void UpdateRect();
	void SceneChange();
	void CreateHitBox();
	void ResetHitBox();

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
	STANCE m_eCurStance;
	STANCE m_ePrevStance;
	float m_fTargetDistX;
	float m_fTargetDistY;
	bool m_bAttack;
	bool m_bAttack2;
	int m_iDeadEffectCnt = 500;
};

