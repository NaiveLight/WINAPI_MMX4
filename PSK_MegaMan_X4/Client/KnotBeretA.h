#pragma once
#include "Actor.h"
class CKnotBeretA :
	public CActor
{

public:
	enum STANCE { IDLE, WALK, ATTACK, DEATH, TURN, END };

public:
	CKnotBeretA();
	virtual ~CKnotBeretA();

	// CActor��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();
	void SceneChange();
	void Dead();

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
	STANCE m_eCurStance;
	STANCE m_ePrevStance;
	float m_fTargetDist;
	bool m_bAttack;
	DWORD m_dwAttackEnd;
};

