#pragma once
#include "Actor.h"

class CPlayer :
	public CActor
{
public:
	enum STANCE { SPAWN, IDLE, ATTACK_NORMAL, ATTACK_BUSTER,
									WALK, WALK_ATT,
									JUMP, JUMP_ATT,
									GROUND, 
									DASH, DASH_ATT,
									WALL, WALL_ATT,
									WALL_JUMP, WALL_JUMP_ATTACK,
									DAMAGE_LOW, DAMAGE_HIGH,
									IDLE_HP_LESS,
									WARP, ST_END};

	enum WEAPON {W_NONE, RF, W_END};
	enum ARMOR {A_NONE, ULTIMATE, A_END};


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

public :
	const int GetLife() { return m_iLife; }
	const bool GetJump() { return m_bJump; }
	const float GetJumpSpeed() { return m_fJumpSpeed; }

public:
	void SetWall(bool bwall) { m_bWall = bwall; }

private:
	virtual void UpdateRect();
	virtual void FrameMove();
	void SceneChange();
	void ScrollMove();

private:
	// 아머 및 무기에 따른 애니메이션 프레임 지정
	void NoArmorNoWeaponScene();
	void NoArmorRFScene();
	void UltiNoWeaponScene();
	void UltiRFScene();

private:
	void Walk();
	void Dash();
	void Jump();
	void Attack();

private:
	TCHAR* m_pLeftFrameKey;
	TCHAR* m_pRightFrameKey;

	STANCE m_eCurStance;
	STANCE m_ePrevStance;

	int m_iOriginHitBoxCX = 0;
	int m_iOriginHitBoxCY = 0;

	//입력 관련해서 변하는 상태
	bool m_bWalk;
	bool m_bDash;
	bool m_bJump;
	bool m_bAttack;
	bool m_bCharge;

	//충돌 관련해서 변하는 상태
	bool m_bGround;
	bool m_bWall;
	bool m_bDamaged;

	//아머타입
	int  m_iArmor;
	//웨폰타입
	int m_iWeapon;

	float m_fAngle;

	// 속도 관련
	float m_fAccelX;
	float m_fAccelY;

	// 대시 관련
	float m_fDashSpeed;
	float m_fDashAccel;
	DWORD m_dwDashStrart;
	DWORD m_dwDashTime;

	// 점프 관련
	float m_fJumpSpeed;
	float m_fJumpAccel;

	int m_iPrevFrame = 0;
	int m_iLife;
};

