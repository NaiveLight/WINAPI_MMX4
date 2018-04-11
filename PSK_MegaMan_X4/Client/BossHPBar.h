#pragma once
#include "GameObject.h"
class CBossHPBar :
	public CGameObject
{
public:
	CBossHPBar();
	virtual ~CBossHPBar();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	const int GetMaxHp() { return m_iMaxHp; }
	const int GetCurHp() { return m_iCurHp; }

	int m_iCurHp;
	int m_iMaxHp;
};

