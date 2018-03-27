#pragma once
#include "GameObject.h"
class CPSText :
	public CGameObject
{
private:
	float m_fOriginX;

public:
	CPSText();
	virtual ~CPSText();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetOriginX() { m_fOriginX = m_tInfo.fX; }
};

