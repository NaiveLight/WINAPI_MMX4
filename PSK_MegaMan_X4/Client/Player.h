#pragma once
#include "Actor.h"

class CPlayer :
	public CActor
{
public:
	enum STANCE {IDLE, ATT, CHARGE_ATT, WALK, WALK_ATT, DASH, DASH_ATT, DAMAGED, ST_END };
	enum WEAPON {W_NONE, LW, RF, W_END};
	enum ARMOR {A_NONE, FORTH, ULTIMATE, A_END};

public:
	CPlayer();
	virtual ~CPlayer();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void ProcessInput();
	void Move();
	void Attack();
	void Jump();
	void Dash();
	void FrameMove();
	void SceneChange();
	void ScrollMove();

private:
	TCHAR* m_pLeftFrameKey;
	TCHAR* m_pRightFrameKey;

	STANCE m_eCurStance;
	STANCE m_ePrevStance;
	
	bool m_bAttack;
	bool m_bJump;
	bool m_bDash;
	bool m_bCharge;
	bool m_bWall;
	bool m_bIsGround;
	bool m_bDamage;

	//아머타입
	int  m_iArmor;
	//웨폰타입
	int m_iWeapon;

	float m_fAngle;
};

