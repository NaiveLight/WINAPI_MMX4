#pragma once
#include "GameObject.h"
class CLB_X :
	public CGameObject
{
public:
	enum STANCE {IDLE, TALK,  RUNOUT, ANGRY, END};

public:
	CLB_X();
	virtual ~CLB_X();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetStance(STANCE eStance) { m_eCurStance = eStance; SceneChange(); }

private:
	void FrameMove();
	void SceneChange();

private:
	STANCE m_ePrevStance;
	STANCE m_eCurStance;
	bool m_bIsPlayed;
	DWORD m_dwStop;
};

