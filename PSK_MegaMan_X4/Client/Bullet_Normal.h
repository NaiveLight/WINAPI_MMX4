#pragma once
#include "Bullet.h"
class CBullet_Normal :
	public CBullet
{
public:
	CBullet_Normal();
	virtual ~CBullet_Normal();

	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void FrameMove();

private:
	void CollisionCheck(OBJECT_ID eID);

private:
	TCHAR* m_LeftKey;
	TCHAR* m_RightKey;
};

