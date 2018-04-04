#include "stdafx.h"
#include "Player.h"
#include "PlayerHPBar.h"
#include "Bullet_Normal.h"
#include "Bullet_SemiBuster.h"
#include "Bullet_FullBuster.h"
#include "Effect_NB_Fire.h"
#include "Effect_Charge.h"
#include "Effect_Charge_Body.h"


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
	m_dwDashTime = 1000;
	m_dwChargeTime = 1000;

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
	
	//if (m_fVelocityX == 0 && m_fVelocityY == 0 && !m_bWalk && !m_bDash && !m_bJump)
	//{
	//	if (m_bAttack)
	//		m_eCurStance = ATTACK_NORMAL;
	//	else
	//		m_eCurStance = IDLE;
	//}

	//if (KeyManager->KeyDown('Z') && !m_bJump)
	//{
	//	//대시
	//	m_bDash = true;
	//	//대시 사운드 이펙트

	//}
	//else if (KeyManager->KeyDown('X'))
	//{
	//	//점프
	//	if (m_bGround && !m_bJump)
	//	{
	//		m_bGround = false;
	//		m_bJump = true;
	//	}
	//	//점프 사운드 이펙트
	//}

	//if (m_bDash)
	//{
	//	m_fVelocityX = m_fDashSpeed;

	//	if (!m_bJump && !m_bAttack)
	//		m_eCurStance = DASH;
	//	else if (!m_bJump && m_bAttack)
	//		m_eCurStance = DASH_ATT;
	//}

	//if (KeyManager->KeyPressing(VK_LEFT))
	//{
	//	if (!m_bIsLeft && m_bDash)
	//	{
	//		m_bWalk = true;
	//		m_bIsLeft = true;
	//		m_pFrameKey = m_pLeftFrameKey;
	//		m_fVelocityX = m_fSpeedX;
	//	}
	//}
	//else if (KeyManager->KeyPressing(VK_RIGHT))
	//{
	//	if (m_bIsLeft && m_bDash)
	//	{
	//		m_bWalk = true;
	//		m_bIsLeft = false;
	//		m_pFrameKey = m_pRightFrameKey;
	//		m_fVelocityX = m_fSpeedX;
	//	}
	//}
	//else if(!m_bDash)
	//{
	//	m_bWalk = false;
	//	m_fVelocityX = 0.f;
	//}

	//if (m_bIsLeft)
	//	m_fVelocityX *= -1.f;



	Walk();
	Dash();
	Jump();
	Attack();

	//m_tInfo.fX += m_fVelocityX;
	//m_tInfo.fY += m_fVelocityY;



	//switch (m_eCurStance)
	//{
	//case SPAWN:
	//	cout << "SPAWN\n";
	//	break;
	//case IDLE:
	//	cout << "IDLE\n";
	//	break;
	//case ATTACK_NORMAL:
	//	cout << "ATTACK_NORMAL\n";
	//	break;
	//case WALK:
	//	cout << "WALK\n";
	//	break;
	//case WALK_ATT:
	//	cout << "WALK_ATT\n";
	//	break;
	//case JUMP:
	//	cout << "JUMP\n";
	//	break;
	//case JUMP_ATT:
	//	cout << "JUMP_ATT\n";
	//	break;
	//case GROUND:
	//	cout << "GROUND\n";
	//	break;
	//case DASH:
	//	cout << "DASH\n";
	//	break;
	//case DASH_ATT:
	//	cout << "DASH_ATT\n";
	//	break;
	//case WALL:
	//	cout << "WALL\n";
	//	break;
	//case WALL_ATT:
	//	cout << "WALL_ATT\n";
	//	break;
	//case WALL_JUMP:
	//	cout << "WALL_JUMP\n";
	//	break;
	//case WALL_JUMP_ATTACK:
	//	cout << "IDLE\n";
	//	break;
	//}

	if (m_tInfo.fX < 15)
		m_tInfo.fX = 15;

	return PLAY;
}

void CPlayer::LateUpdate()
{
	if (m_eCurStance == DAMAGE_HIGH || m_eCurStance == DAMAGE_LOW)
	{
		//Damaged();
	}

	UpdateRect();

	m_bGround = CCollision::PlayerToGround(this, GameManager->GetObjList(OBJ_GROUND));
	//m_bWall = CCollision::PlayerToWall(this, GameManager->GetObjList(OBJ_GROUND));

	if (m_bGround)
		m_bWall = false;
	//if (m_bWall)
	//	cout << "응 벽이야 \n";


	//system("cls");

	//if (m_bGround)
	//	cout << "Ground \n";
	//if (m_bWalk)
	//	cout << "Walk\n";
	//if (m_bDash)
	//	cout << "DASH\n";
	//if (m_bJump)
	//	cout << "Jump\n";
	//if (m_bWall)
	//	cout << "Wall\n";


	//if (m_bGround)
	//	cout << "응 땅이야\n";

	if (m_eCurStance != SPAWN)
	{
		if (m_bDamaged)
		{
			m_eCurStance = DAMAGE_LOW;
		}
		else if (m_bWall)
		{
			if (m_bAttack && m_bJump)
				m_eCurStance = WALL_JUMP_ATTACK;
			else if (m_bAttack)
				m_eCurStance = WALL_ATT;
			else if (m_bJump)
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
				m_eCurStance = IDLE;
		}
	}


	SceneChange();
	FrameMove();
	ScrollMove();

	//system("cls");
	//cout << ((m_eCurStance == WALK) ? ("WALK") : ("WALKATT" ))<< endl;
	//cout << m_tFrame.iStart << endl;
	//cout << m_tFrame.iEnd << endl;
	////attack 후 다시 원래 모션으로 돌리기
	//switch (m_eCurStance)
	//{
	//case WALK_ATT:
	//}
}

void CPlayer::Render(HDC hDC)
{
	DrawHitBox(hDC);
	DrawObjectScroll(hDC, m_pFrameKey);
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

	if (BUFCX * 0.65f + fScrollX < m_tInfo.fX && m_fVelocityX > 0)
		GameManager->SetScrollX(m_fVelocityX);
	if (BUFCX * 0.35f + fScrollX > m_tInfo.fX && m_fVelocityX < 0)
		GameManager->SetScrollX(m_fVelocityX);

	if (4230 >= m_tInfo.fX && m_tInfo.fX >= 3800)
	{
		if (m_fVelocityX > 0)
			GameManager->SetScrollY(0.5f);
		else if (m_fVelocityX < 0)
			GameManager->SetScrollY(-0.5f);
	}

	//system("cls");
	//cout << "X: " << m_tInfo.fX << endl;
	//cout << "Y: " << m_tInfo.fY << endl;

	//cout << "SCROLL Y: " << fScrollY;
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
				m_tFrame.dwSpeed = 80;
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
		case IDLE:
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
			m_tFrame.iStart = m_tFrame.iEnd;
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
		case DAMAGE_LOW:
			m_tFrame.iStart = 0;
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
			m_tFrame.iStart = m_iPrevFrame + 1;
		else
			m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;
	case WALK_ATT:
		m_tFrame.iScene = 5;
		m_tFrame.iStart = m_iPrevFrame + 1;
		m_tFrame.iEnd = m_iPrevFrame + 3;
		if (m_tFrame.iStart >= 13)
		{
			m_tFrame.iStart %= 16;
			m_tFrame.iEnd %= 16;
		}
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
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
		m_tFrame.iStart = m_iPrevFrame + 1;
		m_tFrame.iEnd = m_iPrevFrame + 3;
		if (m_tFrame.iStart >= 3)
		{
			m_tFrame.iStart %= 8;
			m_tFrame.iEnd %= 8;
		}
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
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
		m_tFrame.dwSpeed = 50;
		break;
	case WALL:
		m_tFrame.iScene = 11;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;

	case WALL_ATT:
		m_tFrame.iScene = 12;
		m_tFrame.iStart = m_iPrevFrame;
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

	case DAMAGE_LOW:
		m_tFrame.iScene = 15;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 80;
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
		}
	}
	else if (m_bDash)
	{
		m_fAccelX = m_fDashSpeed;

		if (KeyManager->KeyUp('Z'))
		{
			m_tFrame.iStart = 4;
			m_fAccelX = 0;
		}

		if (m_bJump && m_bWalk)
		{
			m_iHitBoxCX = m_iOriginHitBoxCX;
			m_iHitBoxCY = m_iOriginHitBoxCY;
			m_fAccelX = m_fDashSpeed;
		}
		else if (m_bJump ||
			KeyManager->KeyDown(VK_LEFT) ||
			KeyManager->KeyDown(VK_RIGHT) ||
			m_dwDashStrart + m_dwDashTime < GetTickCount())
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
				m_fAccelX = 8.f;
				if (!m_bIsLeft)
					m_fAccelX *= -1.f;

				m_fVelocityX = m_fAccelX;
				m_fVelocityY = m_fJumpSpeed - 3;
				m_bWallKick = true;
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
			//else if (m_bWall)
			//{
			//	m_fAccelX = 5.f;
			//	if (!m_bIsLeft)
			//		m_fAccelX *= -1.f;

			//	m_fVelocityX = m_fAccelX;
			//}

			m_fVelocityY = m_fJumpSpeed;
		}
	}
	else
	{
		if(!m_bWall)
			m_fVelocityY += m_fJumpAccel;
		if (m_bWall)
			m_fVelocityY += 2.5f;

		if (m_bGround || m_bWall)
			m_bJump = false;

		if (KeyManager->KeyUp('X') && m_fVelocityY < 0)
			m_fVelocityY *= -1;
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

		CGameObject* pEffect = CAbstractFactory<CEffect_NB_Fire>::CreateObj(L"E_NB_FIRE_L", 4, 5, 0, 1);
		pEffect->SetTarget(this);
		GameManager->AddObject(pEffect, OBJ_EFFECT);
		// create normal bullet
		CGameObject* pBullet = CAbstractFactory<CBullet_Normal>::CreateObj(L"BULLET_NBR", 4, 5, 0, 1);
		pBullet->SetTarget(this);
		GameManager->AddObject(pBullet, OBJ_BULLET);
	}
	else
	{
		if (!m_bCharge && m_dwAttackStart + 500 < GetTickCount())
		{
			if (KeyManager->KeyPressing('C') || KeyManager->KeyDown('V'))
			{
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
				if (m_dwChargeStart + 500 < GetTickCount())
				{
					CGameObject* pEffect = CAbstractFactory<CEffect_Charge_Body>::CreateObj(L"E_CHARGE_BODY", 3, 4, 0, 1);
					pEffect->SetSize(80, 80);
					pEffect->SetTarget(this);
					GameManager->AddObject(pEffect, OBJ_EFFECT);
				}
			}

			if (!m_bBodyEffectGreen)
			{
				if (m_dwChargeStart + m_dwChargeTime < GetTickCount())
				{
					CGameObject* pEffect = CAbstractFactory<CEffect_Charge>::CreateObj(L"E_CHARGE_G", 9, 10, 0, 1);
					pEffect->SetTarget(this);
					GameManager->AddObject(pEffect, OBJ_EFFECT);

					pEffect = CAbstractFactory<CEffect_Charge_Body>::CreateObj(L"E_CHARGE_BODY_G", 3, 4, 0, 1);
					pEffect->SetTarget(this);
					GameManager->AddObject(pEffect, OBJ_EFFECT);

					m_bBodyEffectGreen = true;
				}
			}

			//create charge 2 effect
			if (KeyManager->KeyUp('C') || KeyManager->KeyUp('V'))
			{
				cout << "응 차지 키 뗐어\n";
				if (m_dwChargeStart + m_dwChargeTime < GetTickCount())
				{
					// create full buster bullet & Effect
					CGameObject* pBullet = CAbstractFactory<CBullet_FullBuster>::CreateObj(L"BULLET_BBR", 2, 3, 0, 1);
					pBullet->SetTarget(this);
					GameManager->AddObject(pBullet, OBJ_BULLET);
				}
				else
				{
					// create semi buster bullet & effect
					CGameObject* pBullet = CAbstractFactory<CBullet_SemiBuster>::CreateObj(L"BULLET_BSR", 6, 7, 0, 1);
					pBullet->SetTarget(this);
					GameManager->AddObject(pBullet, OBJ_BULLET);
				}

				m_bAttack = true;
				m_bCharge = false;
				m_bBodyEffectBlue = false;
				m_bBodyEffectGreen = false;
				m_iPrevFrame = m_tFrame.iStart;

				//remove charge effect
			}
			m_iPrevFrame = m_tFrame.iStart;
		}
	}


}
