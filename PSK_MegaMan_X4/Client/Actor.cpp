#include "stdafx.h"
#include "Actor.h"


CActor::CActor()
	:m_iCurHP(0), m_iMaxHP(0), m_iAttack(0), m_bIsDead(false), m_bIsDamaged(false)
{
}

CActor::~CActor()
{
}

