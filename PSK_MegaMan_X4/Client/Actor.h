#pragma once
#include "GameObject.h"

// ���� ������ �����̰� ������ �ϴ� ��� ������Ʈ�� Actor Ŭ������ ��ӹ޾Ƽ� �����Ѵ�.

class CActor :
	public CGameObject
{
	// HP
	int m_iMaxHp;
	int m_iCurHp;

	float m_fJumpPower;
	
	float m_fVelocityX;
	float m_fVelocityY;
	float m_fAccelX;
	float m_fAccelY;




public:
	CActor();
	virtual ~CActor();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	//	LateInit �������̵�
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;



};

