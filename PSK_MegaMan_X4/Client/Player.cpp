#include "stdafx.h"
#include "Player.h"
#include "PlayerHPBar.h"
#include "Bullet_Normal.h"
#include "Bullet_SemiBuster.h"
#include "Bullet_FullBuster.h"
#include "Effect_NB_Fire.h"
#include "Effect_Charge.h"
#include "Effect_Charge_Body.h"
#include "Effect_Dash.h"
#include "Effect_Wall.h"
#include "Effect_WallKick.h"

CPlayer::CPlayer()
	:m_pLeftFrameKey(nullptr), m_pRightFrameKey(nullptr),
	m_eCurStance(ST_END), m_ePrevStance(ST_END),
	m_bWalk(false), m_bDash(false), m_bJump(false), m_bAttack(false), m_bCharge(false),
	m_bGround(false), m_bWall(false), m_bDamaged(false),
	m_fAccelX(0.f), m_fAccelY(0.f)
	, m_dwDashStrart(0), m_dwDashTime(0),
	m_dwChargeStart(0), m_dwChargeTime(0),
	m_iLife(0)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init()
{
	m_tInfo.fX = 150.f;
	m_tInfo.fY = 0.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_iOriginHitBoxCX = m_iHitBoxCX = 25;
	m_iOriginHitBoxCY = m_iHitBoxCY = 40;

	m_pLeftFrameKey = L"X_LEFT";
	m_pFrameKey = m_pRightFrameKey = L"X_RIGHT"; 

	SetStartPos(m_tInfo.fX, m_tInfo.fY);
	
	m_bIsActive = true;
	m_bIsLeft = false;
	m_bGround = false;
	m_iFrameCnt = 17;
	m_iSceneCnt = 19;
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 16;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
	m_eCurStance = m_ePrevStance = SPAWN;
	m_iArmor = A_NONE;
	m_iWeapon = W_NONE;
	

	m_fSpeedX = 2.f;
	m_fSpeedY = -6.f;
	m_fVelocityX = 0.f;
	m_fVelocityY = 8.f;
	m_fJumpSpeed = -6.f;
	m_fJumpAccel = 0.25f;
	m_fDashSpeed = 3.5f;
	m_fDashAccel = 0.25f;
	m_dwDashTime = 500;
	m_dwChargeTime = 1200;

	m_iCurHP = m_iMaxHP = 15;
	m_iLife = 3;
}

void CPlayer::LateInit()
{
	CGameObject* pHPbar = CAbstractFactory<CPlayerHPBar>::CreateObj(25, BUFCY / 3.5f, L"PLAYER_HP_BAR", 1, 2, 0, 1);
	pHPbar->SetTarget(this);
	GameManager->AddObject(pHPbar, OBJ_UI);
}

OBJECT_STATE CPlayer::Update()
{
	CGameObject::LateInit();

	if (!m_bIsActive)
	{
		//Dead();
		return PLAY;
	}

	if (m_eCurStance == SPAWN)
	{
		m_tInfo.fY += m_fVelocityY;
		return PLAY;
	}

	if (m_eCurStance == DAMAGE_HIGH || m_eCurStance == DAMAGE_LOW)
		return PLAY;

	Walk();
	Dash();
	Jump();
	Attack();

	// y스크롤 총 30 먹여줘야함 172 302

	if (m_eCurStance != SPAWN)
	{
		if (m_bDamaged)
		{
			m_eCurStance = DAMAGE_LOW;
		}
		else if (m_bWall)
		{
			if (m_bAttack && m_bWallKick)
				m_eCurStance = WALL_JUMP_ATTACK;
			else if (m_bAttack)
				m_eCurStance = WALL_ATT;
			else if (m_bWallKick)
				m_eCurStance = WALL_JUMP;
			else
				m_eCurStance = WALL;
		}
		else if (m_bWallKick)
		{
			if (m_bAttack)
				m_eCurStance = WALL_JUMP_ATTACK;
			else
				m_eCurStance = WALL_JUMP;
		}
		else if (m_bWalk && m_bGround && !m_bDash && !m_bJump)
		{
			if (m_bAttack)
				m_eCurStance = WALK_ATT;
			else
				m_eCurStance = WALK;
		}
		else if (m_bJump && !m_bGround)
		{
			if (m_bAttack)
				m_eCurStance = JUMP_ATT;
			else
				m_eCurStance = JUMP;
		}
		else if (m_bDash)
		{
			if (m_bAttack)
				m_eCurStance = DASH_ATT;
			else
				m_eCurStance = DASH;
		}
		else if (!m_bWalk && !m_bJump && m_bGround)
		{
			if (m_bAttack && !m_bCharge)
				m_eCurStance = ATTACK_NORMAL;
			else if (!m_bAttack)
			{
				if ((m_iCurHP / (float)m_iMaxHP) > 0.5f)
					m_eCurStance = IDLE;
				else
					m_eCurStance = IDLE_HP_LESS;
			}
		}
	}

	if (m_tInfo.fX < 15)
		m_tInfo.fX = 15;

	return PLAY;
}

void CPlayer::LateUpdate()
{
	if (m_eCurStance == DAMAGE_HIGH || m_eCurStance == DAMAGE_LOW)
	{
		Damaged();
	}

	FrameMove();
	UpdateRect();


	m_bGround = CCollision::PlayerToGround(this, GameManager->GetObjList(OBJ_GROUND));
	CCollision::PlayerToMonster(this, GameManager->GetObjList(OBJ_MONSTER));
	CCollision::PlayerToMonster(this, GameManager->GetObjList(OBJ_BOSS));

	if (m_bGround)
		m_bWall = false;

	if (m_eCurStance == DAMAGE_LOW)
		m_dwDamagedStart = GetTickCount() + 2000;

	if (m_dwDamagedStart < GetTickCount())
		m_bInvincible = false;

	SceneChange();
	ScrollMove();
}

void CPlayer::Render(HDC hDC)
{
	if (m_bInvincible)
	{
		if(g_iFrame % 2 == 0)
			DrawObjectScroll(hDC, m_pFrameKey);
	}
	else
	{
		DrawObjectScroll(hDC, m_pFrameKey);
	}
}

void CPlayer::Release()
{
}

void CPlayer::UpdateRect()
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();

	m_tTexRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tTexRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tTexRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tTexRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2);
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2);
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2);
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2);
}

void CPlayer::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{
		switch (m_iArmor)
		{
		case A_NONE:
			switch(m_iWeapon)
			{
			case W_NONE:
				NoArmorNoWeaponScene();
				break;
			case RF:
				NoArmorRFScene();
				break;
			}
			break;
		case ULTIMATE:
			switch (m_iWeapon)
			{
			case W_NONE:
				UltiNoWeaponScene();
				break;
			case RF:
				UltiRFScene();
				break;
			}
			break;
		}
		m_ePrevStance = m_eCurStance;
	}
}

void CPlayer::ScrollMove()
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();

	if (BUFCX * 0.6f + fScrollX < m_tInfo.fX && m_fVelocityX > 0)
		GameManager->SetScrollX(m_fVelocityX);
	if (BUFCX * 0.4f + fScrollX > m_tInfo.fX && m_fVelocityX < 0)
		GameManager->SetScrollX(m_fVelocityX);

	//if(BUFCY * 0.6f + fScrollX < m_tInfo.fX && m_fVelocityX > 0)

	if (4230 >= m_tInfo.fX && m_tInfo.fX >= 3800)
	{
		if (m_fVelocityX > 0)
			GameManager->SetScrollY(0.5f);
		else if (m_fVelocityX < 0)
			GameManager->SetScrollY(-0.3f);
	}
}

void CPlayer::FrameMove()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		// 애니메이션 실행 도중에도 다르게 처리되는 것들이 있다.
		switch (m_tFrame.iScene)
		{
		case SPAWN:
			if (!m_bGround)
				return;
			if (m_tFrame.iStart == 15)
				m_tFrame.dwSpeed = 200;
			break;
		case JUMP:
			if (m_bGround)
			{
				m_eCurStance = GROUND;
				m_bJump = false;
			}
			break;
		case DASH:
			if (m_bDash && m_tFrame.iStart == 3)
			{
				m_tFrame.dwSpeed = 50;
				return;
			}
			break;
		case DASH_ATT:
			if (m_bDash && m_tFrame.iStart == 3)
			{
				m_eCurStance = DASH;
				m_bAttack = false;
				return;
			}
			break;

		case WALL:
			if (m_tFrame.iStart == 0)
				//SoundManager->PlaySound(L"SPIKE_ATTACK.wav");
			break;
		}

		++m_tFrame.iStart;

		m_tFrame.dwTime = GetTickCount();
	}

	// 각 상황마다 다르게 처리 해주어야한다.
	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		switch (m_eCurStance)
		{
		//SPAWN은 끝나면 IDLE상태로 변환 되어야 한다.
		case SPAWN:
			m_eCurStance = IDLE;
			break;
		case IDLE: case IDLE_HP_LESS:
			m_tFrame.iStart = 0;
			break;
		// IDLE에서 ATTACK했을시 다시 IDLE로 돌아가야함
		case ATTACK_NORMAL:
			m_bAttack = false;
			m_eCurStance = IDLE;
			break;
		case WALK:
			m_tFrame.iStart = 2;
			break;
		case WALK_ATT:
			if (m_tFrame.iStart == 16)
				m_tFrame.iStart = 2;
			m_eCurStance = WALK;
			m_bAttack = false;
			break;
		case JUMP:
			m_tFrame.iStart = m_tFrame.iEnd;
			break;
		case JUMP_ATT:
			m_tFrame.iStart =m_iPrevFrame;
			m_eCurStance = JUMP;
			m_bAttack = false;
			break;
		case GROUND:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = IDLE;
			break;
		case DASH:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_bDash = false;
			m_iHitBoxCX = m_iOriginHitBoxCX;
			m_iHitBoxCY = m_iOriginHitBoxCY;
			m_eCurStance = IDLE;
			break;
		case DASH_ATT:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = DASH;
			m_bAttack = false;
			break;	
		case WALL:
			m_tFrame.iStart = m_tFrame.iEnd;
			if (!m_bWallEffectCreate)
			{
				CGameObject* pEffect = CAbstractFactory<CEffect_Wall>::CreateObj(L"E_WALL_R", 7, 8, 0, 1);
				pEffect->SetTarget(this);
				pEffect->SetIsLeft(m_bIsLeft);
				GameManager->AddObject(pEffect, OBJ_EFFECT);
				//SoundManager->PlaySound(L"DASH.wav", CSoundManager::EFFECT);
			}
			break;
		case WALL_ATT:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = WALL;
			m_bAttack = false;
			break;
		case WALL_JUMP:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_bWallKick = false;
			break;

		case WALL_JUMP_ATTACK:
			m_tFrame.iStart = m_tFrame.iEnd;
			m_eCurStance = WALL_JUMP;
			m_bWallKick = false;
			m_bAttack = false;
			break;
		case DAMAGE_LOW:
			m_tFrame.iStart = 0;
			if (m_dwDamagedStart + 2000 < GetTickCount())
			{
				m_bDamaged = false;
				m_eCurStance = IDLE;
			}
			break;
		}
	}
}

void CPlayer::NoArmorNoWeaponScene()
{
	m_pLeftFrameKey = L"X_LEFT";
	m_pRightFrameKey = L"X_RIGHT";
	m_pFrameKey = m_bIsLeft ? m_pLeftFrameKey : m_pRightFrameKey;
	switch (m_eCurStance)
	{
	case SPAWN:
		m_tFrame.iScene = 0;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 16;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 100;
		break;
	case IDLE:
		m_tFrame.iScene = 1;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 200;
		break;
	case ATTACK_NORMAL:
		m_tFrame.iScene = 2;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 7;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 30;
		break;
	case WALK:
		m_tFrame.iScene = 4;
		if (m_ePrevStance == WALK_ATT)
			m_tFrame.iStart = m_iPrevFrame;
		else
			m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;
	case WALK_ATT:
		m_tFrame.iScene = 5;
		m_tFrame.iStart = m_iPrevFrame;
		m_tFrame.iEnd = m_iPrevFrame+1;
		if (m_tFrame.iStart >= 13)
		{
			m_tFrame.iStart %= 16;
			m_tFrame.iEnd %= 16;
		}
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 20;
		break;
	case JUMP:
		m_tFrame.iScene = 6;
		if (m_ePrevStance == WALK_ATT)
			m_tFrame.iStart = 6;
		else
			m_tFrame.iStart = 0;
		m_tFrame.iEnd = 7;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;
	case JUMP_ATT:
		m_tFrame.iScene = 7;
		m_tFrame.iStart = m_iPrevFrame;
		m_tFrame.iEnd = m_iPrevFrame+1;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 20;
		break;
	case GROUND:
		m_tFrame.iScene = 8;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;
	case DASH:
		m_tFrame.iScene = 9;
		if (m_ePrevStance == DASH_ATT)
			m_tFrame.iStart = 3;
		else
			m_tFrame.iStart = 0;
		m_tFrame.iEnd = 7;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 30;
		break;
	case DASH_ATT:
		m_tFrame.iScene = 10;
		m_tFrame.iStart = m_iPrevFrame - 2;
		m_tFrame.iEnd = m_iPrevFrame + 3;
		if (m_tFrame.iStart >= 3)
		{
			m_tFrame.iStart %= 8;
			m_tFrame.iEnd %= 8;
		}
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 20;
		break;

	case WALL:
		m_tFrame.iScene = 11;
		if(m_ePrevStance != WALL_ATT)
			m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 30;
		break;

	case WALL_ATT:
		m_tFrame.iScene = 12;
		m_tFrame.iStart = m_tFrame.iEnd;
		m_tFrame.iEnd = 3;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;

	case WALL_JUMP:
		m_tFrame.iScene = 13;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;

	case WALL_JUMP_ATTACK:
		m_tFrame.iScene = 14;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 20;
		break;

	case DAMAGE_LOW:
		m_tFrame.iScene = 15;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 100;
		break;

	case IDLE_HP_LESS:
		m_tFrame.iScene = 17;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 200;
		break;
	}
}

void CPlayer::NoArmorRFScene()
{
	m_pLeftFrameKey = L"X_LEFT";
	m_pRightFrameKey = L"X_RIGHT";
	m_pFrameKey = m_bIsLeft ? m_pLeftFrameKey : m_pRightFrameKey;

	//switch (m_eCurStance)
	//{

	//}
}

void CPlayer::UltiNoWeaponScene()
{
}

void CPlayer::UltiRFScene()
{
}

void CPlayer::ApplyDamage(int iDamage)
{
	if (!m_bInvincible)
	{
		CActor::ApplyDamage(iDamage);
		SoundManager->StopSound(CSoundManager::PLAYER);
		SoundManager->PlaySound(TEXT("Damage.wav"), CSoundManager::PLAYER);

		if (m_iCurHP <= 0)
		{
			m_bIsDead = true;
		}
		else
		{
			m_eCurStance = DAMAGE_LOW;
			m_bInvincible = true;
		}
	}
}

void CPlayer::Walk()
{
	//좌우 키 입력
	if (KeyManager->KeyPressing(VK_LEFT))
	{
		m_bWalk = true;
		m_bIsLeft = true;
		m_fAccelX = m_fSpeedX;
		m_pFrameKey = m_pLeftFrameKey;
	}
	else if (KeyManager->KeyPressing(VK_RIGHT))
	{
		m_bWalk = true;
		m_bIsLeft = false;
		m_fAccelX = m_fSpeedX;
		m_pFrameKey = m_pRightFrameKey;
	}
	else
	{
		m_bWalk = false;
		m_fAccelX = 0.f;
	}

	if (m_bIsLeft && m_bWalk)
		m_fAccelX *= -1;
}

void CPlayer::Dash()
{
	if (!m_bDash && !m_bJump)
	{
		if (KeyManager->KeyDown('Z'))
		{
			m_dwDashStrart = GetTickCount();
			m_bDash = true;
			m_iHitBoxCX = 45;
			m_iHitBoxCY = 40;

			CGameObject* pEffect = CAbstractFactory<CEffect_Dash>::CreateObj(L"E_DASH", 6, 7, 0, 1);
			pEffect->SetTarget(this);
			pEffect->SetIsLeft(m_bIsLeft);
			GameManager->AddObject(pEffect, OBJ_EFFECT);
			SoundManager->PlaySound(L"DASH.wav", CSoundManager::EFFECT);
		}
	}
	else if (m_bDash && !m_bWall)
	{
		m_fAccelX = m_fDashSpeed;

		if (KeyManager->KeyUp('Z') || m_dwDashStrart + m_dwDashTime < GetTickCount())
		{
			m_tFrame.iStart = 4;
			m_fAccelX = 0;
			SoundManager->StopSound(CSoundManager::EFFECT);

			if(m_bGround)
				SoundManager->PlaySound(L"DASH_STOP.wav", CSoundManager::EFFECT);
			m_dwDashStrart = GetTickCount();
		}

		if (m_bJump && m_bWalk)
		{
			m_iHitBoxCX = m_iOriginHitBoxCX;
			m_iHitBoxCY = m_iOriginHitBoxCY;
			m_fAccelX = m_fDashSpeed;
		}
		else if (m_bJump ||
			KeyManager->KeyDown(VK_LEFT) ||
			KeyManager->KeyDown(VK_RIGHT))
		{
			m_iHitBoxCX = m_iOriginHitBoxCX;
			m_iHitBoxCY = m_iOriginHitBoxCY;
			m_bDash = false;
			m_fAccelX = 0;
		}

		if (m_bIsLeft)
			m_fAccelX *= -1.f;
	}
}

void CPlayer::Jump()
{
	m_fVelocityX = m_fAccelX;
	if (!m_bJump)
	{
		if (KeyManager->KeyDown('X'))
		{
			if (m_bWall)
			{
				m_fAccelX = 10.f;
				if (!m_bIsLeft)
					m_fAccelX *= -1.f;

				m_fVelocityX = m_fAccelX;
				m_fVelocityY = m_fJumpSpeed - 3;
				m_bWallKick = true;

				CGameObject* pEffect = CAbstractFactory<CEffect_WallKick>::CreateObj(L"E_WALLKICK_R", 3, 4, 0, 1);
				pEffect->SetTarget(this);
				pEffect->SetIsLeft(m_bIsLeft);
				GameManager->AddObject(pEffect, OBJ_EFFECT);
				SoundManager->PlaySound(L"WALL_JUMP_VOICE.wav", CSoundManager::PLAYER);
				
			}
		}
		else if (KeyManager->KeyPressing('X') && !m_bWall)
		{
			m_bJump = true;

			if (!m_bWalk && m_bDash)
			{
				m_fVelocityX = 0.f;
				m_bDash = false;
				m_iHitBoxCX = m_iOriginHitBoxCX;
				m_iHitBoxCY = m_iOriginHitBoxCY;
			}

			m_fVelocityY = m_fJumpSpeed;
			SoundManager->PlaySound(L"JUMP.wav", CSoundManager::EFFECT);
			SoundManager->PlaySound(L"JUMP_VOICE.wav", CSoundManager::PLAYER);
		}
	}
	else
	{
		if(!m_bWall)
			m_fVelocityY += m_fJumpAccel;
		if (m_bWall)
			m_fVelocityY += 2.5f;

		if (m_bGround || m_bWall)
		{
			m_bJump = false;
			m_bDash = false;
		}
			

		if (KeyManager->KeyUp('X') && m_fVelocityY < 0)
			m_fVelocityY *= -1;
	}

	if (m_bDamaged)
	{
		m_fVelocityX = 0.f;
		m_fVelocityY = m_fJumpSpeed;
		m_fAccelY = 2.5f;
	}

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY += m_fVelocityY + m_fAccelY;
	m_fAccelY = 0;
}

void CPlayer::Attack()
{
	if (KeyManager->KeyDown('C') || KeyManager->KeyDown('V'))
	{
		m_bAttack = true;
		m_iPrevFrame = m_tFrame.iStart;
		m_dwAttackStart = GetTickCount();
		SoundManager->PlaySound(L"bullet.wav", CSoundManager::EFFECT);

		CGameObject* pEffect = CAbstractFactory<CEffect_NB_Fire>::CreateObj(L"E_NB_FIRE_L", 4, 5, 0, 1);
		pEffect->SetTarget(this);
		GameManager->AddObject(pEffect, OBJ_EFFECT);
		// create normal bullet
		CGameObject* pBullet = CAbstractFactory<CBullet_Normal>::CreateObj(L"BULLET_NBR", 4, 5, 0, 1);
		pBullet->SetTarget(this);
		GameManager->AddObject(pBullet, OBJ_BULLET);
		KeyManager->Update();
	}
	else
	{
		if (!m_bCharge && m_dwAttackStart + 500 < GetTickCount())
		{
			if (KeyManager->KeyPressing('C') || KeyManager->KeyPressing('V'))
			{
				SoundManager->PlaySound(L"ChargeStart.wav", CSoundManager::EFFECT);
				m_bCharge = true;
				m_dwChargeStart = GetTickCount();
				// create charge 1 effect 
				CGameObject* pEffect = CAbstractFactory<CEffect_Charge>::CreateObj(L"E_CHARGE", 9, 10, 0, 1);
				pEffect->SetTarget(this);
				GameManager->AddObject(pEffect, OBJ_EFFECT);
			}
		}
		else if(m_bCharge)
		{
			if (!m_bBodyEffectBlue)
			{
				if (m_dwChargeStart + 300 < GetTickCount())
				{
					CGameObject* pEffect = CAbstractFactory<CEffect_Charge_Body>::CreateObj(L"E_CHARGE_BODY", 3, 4, 0, 1);
					pEffect->SetSize(80, 80);
					pEffect->SetTarget(this);
					GameManager->AddObject(pEffect, OBJ_EFFECT);
					m_bBodyEffectBlue = true;
				}
			}

			if (!m_bBodyEffectGreen)
			{
				if (m_dwChargeStart + m_dwChargeTime < GetTickCount())
				{
					SoundManager->PlaySound(L"CHARGING.wav", CSoundManager::EFFECT);
					CGameObject* pEffect = CAbstractFactory<CEffect_Charge>::CreateObj(L"E_CHARGE_G", 9, 10, 0, 1);
					pEffect->SetTarget(this);
					GameManager->AddObject(pEffect, OBJ_EFFECT);

					pEffect = CAbstractFactory<CEffect_Charge_Body>::CreateObj(L"E_CHARGE_BODY_G", 3, 4, 0, 1);
					pEffect->SetTarget(this);
					GameManager->AddObject(pEffect, OBJ_EFFECT);

					pEffect = CAbstractFactory<CEffect_Charge_Body>::CreateObj(L"E_CHARGE_BODY", 3, 4, 0, 1);
					pEffect->SetSize(80, 80);
					pEffect->SetTarget(this);

					m_bBodyEffectGreen = true;
				}
			}

			//create charge 2 effect
			if (KeyManager->KeyUp('C') || KeyManager->KeyUp('V'))
			{
				SoundManager->StopSound(CSoundManager::EFFECT);
				SoundManager->Update();

				if (m_dwChargeStart + m_dwChargeTime < GetTickCount())
				{
					// create full buster bullet & Effect
					CGameObject* pBullet = CAbstractFactory<CBullet_FullBuster>::CreateObj(L"BULLET_BBR", 2, 3, 0, 1);
					pBullet->SetTarget(this);
					GameManager->AddObject(pBullet, OBJ_BULLET);
					SoundManager->StopSound(CSoundManager::EFFECT);

					SoundManager->PlaySound(L"BUSTER.wav", CSoundManager::EFFECT);
				}
				else
				{
					// create semi buster bullet & effect
					CGameObject* pBullet = CAbstractFactory<CBullet_SemiBuster>::CreateObj(L"BULLET_BSR", 6, 7, 0, 1);
					pBullet->SetTarget(this);
					GameManager->AddObject(pBullet, OBJ_BULLET);

					SoundManager->PlaySound(L"SEMIBUSTER.wav", CSoundManager::EFFECT);

				}

				m_bAttack = true;
				m_bCharge = false;
				m_bBodyEffectBlue = false;
				m_bBodyEffectGreen = false;
				m_iPrevFrame = m_tFrame.iStart;
				//remove charge effect
				//SoundManager->Update();
			}
			m_iPrevFrame = m_tFrame.iStart;
		}
	}


}

void CPlayer::Damaged()
{
	m_fVelocityX = m_bIsLeft ? 1.f : -1.f;
	m_fVelocityY -= 2.f;

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY -= m_fVelocityY;

	if (m_tFrame.iStart == m_tFrame.iEnd)
	{
		m_eCurStance = IDLE;
	}
}
