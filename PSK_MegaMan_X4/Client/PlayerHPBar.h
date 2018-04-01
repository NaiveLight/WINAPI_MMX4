#pragma once
#include "GameObject.h"
class CPlayerHPBar :
	public CGameObject
{
public:
	CPlayerHPBar();
	virtual ~CPlayerHPBar();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int m_iMaxHp;
	int m_iCurHp;
	int m_iLife;
};

