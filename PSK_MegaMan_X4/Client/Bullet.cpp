#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	:	m_iAttack(0)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Init()
{
	//m_iAttack = 
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
