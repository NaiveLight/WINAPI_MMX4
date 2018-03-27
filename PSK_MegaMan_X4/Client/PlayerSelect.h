#pragma once
#include "Scene.h"
class CPlayerSelect :
	public CScene
{
public:
	CPlayerSelect();
	virtual ~CPlayerSelect();

	// CScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CGameObject* m_pX;
	bool m_bCreateCursor;
};

