#pragma once
#include "Actor.h"
class CSpikeMarl :
	public CActor
{

public:
	enum STANCE {IDLE, ATTACK_BEGINE, ATTACK, ATTACK_AFTER, TURN, END};

public:
	CSpikeMarl();
	virtual ~CSpikeMarl();

	// CActor��(��) ���� ��ӵ�
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

