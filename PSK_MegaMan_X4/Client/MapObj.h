#pragma once
#include "GameObject.h"
class CMapObj :
	public CGameObject
{
public:
	CMapObj();
	virtual ~CMapObj();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetOriginInfo(INFO& tInfo) { m_tOriginInfo = tInfo; }

private:
	INFO m_tOriginInfo;
	bool m_bIsUpdate;
};

