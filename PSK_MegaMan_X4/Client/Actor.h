#pragma once
#include "GameObject.h"

// 플레이어 혹은 몬스터같은
// 상호작용을 해야하는 오브젝트들을 Actor라 칭하고 그 특징들을 넣을 예정
// 
// HP, ATT

class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() = 0;
	virtual void LateInit() = 0;
	virtual OBJECT_STATE Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	const int GetCurHp() { return m_iCurHP; }
	const int GetMaxHp() { return m_iMaxHP; }
	const float GetHPRatio() { return m_iCurHP / (float)m_iMaxHP; }
	const int GetAttack() { return m_iAttack; }
	const float GetVelocityX(){ return m_fVelocityX; }
	const float GetVelocityY(){ return m_fVelocityY; }
	const bool GetIsDamaged() { return m_bIsDamaged; }

public:
	void SetVelocityX(float fVelX) { m_fVelocityX = fVelX; }
	void SetVelocityY(float fVelY) { m_fVelocityY = fVelY; }
	void SetStartPos(float fX, float fY) { m_fStartX = fX; m_fStartY = fY; }
	void SetPosToStart() { m_tInfo.fX = m_fStartX; m_tInfo.fY = m_fStartY; }
	void SetMaxHP(int iHp) { m_iMaxHP = iHp; }
	void SetCurHP(int iHp) { m_iCurHP = iHp; }
	void SetAttack(int iAtt) { m_iAttack = iAtt; }
	void SetIsDamaged(bool bD) { m_bIsDamaged = bD; }

public:
	virtual void ApplyDamage(int iDamage) 
	{ 
		m_iCurHP -= iDamage; 
		if (m_iCurHP <= 0)
		{
			m_iCurHP = 0;
			m_bIsDead = true;
		}
	}
	

protected:
	int m_iCurHP;
	int m_iMaxHP;
	int m_iAttack;

	float m_fStartX;
	float m_fStartY;

	float m_fVelocityX;
	float m_fVelocityY;

	bool m_bIsDamaged;
	bool m_bIsDead;
};

