#pragma once
#include "GameObject.h"

// �÷��̾� Ȥ�� ���Ͱ���
// ��ȣ�ۿ��� �ؾ��ϴ� ������Ʈ���� Actor�� Ī�ϰ� �� Ư¡���� ���� ����
// 
// HP, ATT

class CActor :
	public CGameObject
{
public:
	CActor();
	virtual ~CActor();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
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

public:
	virtual void ApplyDamage(int iDamage) { m_iCurHP -= iDamage; }
	

protected:
	int m_iCurHP;
	int m_iMaxHP;
	int m_iAttack;

	float m_fStartX;
	float m_fStartY;

	float m_fVelocityX;
	float m_fVelocityY;

	bool m_bIsDamaged;
};

