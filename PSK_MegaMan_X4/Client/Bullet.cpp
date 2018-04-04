#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	:	m_iAttack(0), m_bIsBuster(false)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Init()
{
}

void CBullet::LateInit()
{
}

OBJECT_STATE CBullet::Update()
{
	return PLAY;
}

void CBullet::LateUpdate()
{
}

void CBullet::Render(HDC hDC)
{
}

void CBullet::Release()
{
}
