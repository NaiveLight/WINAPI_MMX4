#pragma once
#include "Bullet.h"
class CBullet_FullBuster :
	public CBullet
{
public:
	CBullet_FullBuster();
	virtual ~CBullet_FullBuster();

	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
};

