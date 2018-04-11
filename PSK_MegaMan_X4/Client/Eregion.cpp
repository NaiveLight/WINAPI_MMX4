#include "stdafx.h"
#include "Eregion.h"
#include "BossHPBar.h"
#include "Effect_Explosion.h"
CEregion::CEregion()
{
}

CEregion::~CEregion()
{
	Release();
}

void CEregion::Init()
{
	m_tInfo.fCX = 500.f;
	m_tInfo.fCY = 300.f;
	m_iHitBoxCX = 50;
	m_iHitBoxCY = 70;

	m_LeftKey = L"B_EREGION_L";
	m_RightKey = L"B_EREGION_R";
	m_pFrameKey = m_RightKey;
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 250;
	m_fVelocityX = 1.5f;
	m_fVelocityY = 1.0f;
	m_eCurStance = IDLE;
	m_iCurHP = m_iMaxHP = 20;
	m_iAttack = 3;
}

void CEregion::LateInit()
{
	m_bIsActive = true;
	m_bAttack = false;

	//CGameObject* pCurHP = CAbstractFactory<CBossHPBar>::CreateObj(BUFCX - 25, BUFCY / 3.f, L"BOSS_HP_BAR", 2, 3, 0, 1);
	//pCurHP->SetTarget(this);
	//GameManager->AddObject(pCurHP, OBJ_UI);
}

OBJECT_STATE CEregion::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
		return DESTROY;

	if (m_bIsDead)
	{
		ResetHitBox();
		if (m_iDeadEffectCnt < 0)
			m_bIsActive = false;
		else
		{
			float fx = (float)(rand() % 101);
			float fy = (float)(rand() % 81);
			
			int random = rand() % 2;
			if (random)
			{
				fx *= -1.f;
				fy *= -1.f;
			}

			SoundManager->PlaySound(L"Exlposion.wav", CSoundManager::MONSTER);

			GameManager->AddObject(
			CAbstractFactory<CEffect_Explosion>::CreateObj(m_tInfo.fX + fx, m_tInfo.fY + fy, L"E_EXPLOSION", 17, 18, 0, 1),
			OBJ_EFFECT);

			m_fVelocityX = -2.f;
			m_fVelocityY = 1.f;

			m_tInfo.fX += m_fVelocityX;
			m_tInfo.fY += m_fVelocityY;
			m_iDeadEffectCnt--;

			if (abs(m_fTargetDistX) > 300)
				m_iDeadEffectCnt = -1;
		}
		return PLAY;
	}

	if (m_bAttack)
		return PLAY;

	//cout << m_tInfo.fY << endl;

	//m_eCurStance = ATTACK_A;

	if (m_fTargetDistX <= 0.f)
	{
		m_bIsLeft = true;
		m_pFrameKey = m_LeftKey;
	}
	else if (m_fTargetDistX > 0.f)
	{
		m_bIsLeft = false;
		m_pFrameKey = m_RightKey;
	}

	if (20 <= abs(m_fTargetDistX) && abs(m_fTargetDistX))
	{
		m_eCurStance = IDLE;
		m_fVelocityX = m_bIsLeft ? -2.f : 2.f;
	}
	else if (m_bIsLeft && m_fTargetDistX >= -5 && m_eCurStance != ATTACK_A)
	{
		m_eCurStance = ATTACK_A;
		m_fVelocityX = 0.f;
	}
	else if (!m_bIsLeft && m_fTargetDistX <= 5 && m_eCurStance != ATTACK_A)
	{
		m_eCurStance = ATTACK_A;
		m_fVelocityX = 0.f;
	}

	if (m_tInfo.fY > 100 || m_tInfo.fY < 50)
	{
		m_fVelocityY *= -1.f;
	}

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY += m_fVelocityY;

	return PLAY;
}

void CEregion::LateUpdate()
{
	UpdateRect();

	m_fTargetDistX = m_pTarget->GetInfo().fX - m_tInfo.fX;
	m_fTargetDistY = m_pTarget->GetInfo().fY - m_tInfo.fY;

	if (m_bIsDead)
		return;

	FrameMove();
	SceneChange();
}

void CEregion::Render(HDC hDC)
{
	//DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CEregion::Release()
{
}

void CEregion::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (m_eCurStance == IDLE)
		{
			if (m_tFrame.iStart == 0 || m_tFrame.iStart == 2)
				SoundManager->PlaySound(L"BOSS_MOVE.wav", CSoundManager::MONSTER);
		}

		++m_tFrame.iStart;

		switch (m_eCurStance)
		{
		case ATTACK_A:
			if (m_tFrame.iStart == 6)
			{
				SoundManager->PlaySound(L"BOSS_ATTACK.wav", CSoundManager::MONSTER);
				m_tFrame.dwSpeed = 2000;
				CreateHitBox();
				GameManager->CameraShakingStart(1.f, 500);
			}
			break;
		case ATTACK_B:
			if (m_tFrame.iStart == m_tFrame.iEnd-1)
			{
				m_tFrame.dwSpeed = 3000;
			}
			break;
		}
		m_tFrame.dwTime = GetTickCount();
	}

	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			break;
		case ATTACK_A:
			m_tFrame.iStart = 0;
			m_tFrame.dwSpeed = 150;
			ResetHitBox();
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			m_bAttack = false;
			break;
		case ATTACK_B:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			m_bAttack = false;
			break;
		}
	}
}

void CEregion::UpdateRect()
{
	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);
}

void CEregion::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{
		switch (m_eCurStance)
		{
		case IDLE:
			m_tFrame.iScene = 0;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 80;
			break;
		case ATTACK_A:
			m_bAttack = true;
			m_tFrame.iScene = 1;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
			break;
		case ATTACK_B:
			m_bAttack = true;
			m_tFrame.iScene = 2;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			break;

		}
		m_ePrevStance = m_eCurStance;
	}
}

void CEregion::CreateHitBox()
{
	if (!m_bIsLeft)
	{
		m_tHitBoxRect.right = m_tInfo.fX - 30;
		m_tHitBoxRect.left = m_tHitBoxRect.right - 50;
	}
	else
	{
		m_tHitBoxRect.left = m_tInfo.fX + 30;
		m_tHitBoxRect.right = m_tHitBoxRect.left + 50;
	}

	m_tHitBoxRect.top = m_tInfo.fY + 30;
	m_tHitBoxRect.bottom = m_tHitBoxRect.top + 70;
}

void CEregion::ResetHitBox()
{
	m_tHitBoxRect = {};
}
