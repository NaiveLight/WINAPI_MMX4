#pragma once
#include "GameObject.h"

// 게임 내에서 움직이고 행위를 하는 모든 오브젝트는 Actor 클래스를 상속받아서 구현한다.

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

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	//	LateInit 오버라이딩
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;



};

