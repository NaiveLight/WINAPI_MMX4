#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	:m_pLeftFrameKey(nullptr), m_pRightFrameKey(nullptr),
	m_eCurStance(ST_END), m_ePrevStance(ST_END),
	m_bAttack(false), m_bJump(false), m_bDash(false), m_bWall(false), m_bCharge(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Init()
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
	m_iHitBoxCX = 60;
	m_iHitBoxCY = 100;

	m_pLeftFrameKey = L"X_LEFT";
	m_pFrameKey = m_pRightFrameKey = L"X_RIGHT";

	m_bIsActive = true;
	m_bIsLeft = false;
	m_tFrame.iScene = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 16;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
	m_eCurStance = m_ePrevStance = IDLE;
	m_iArmor = A_NONE;
	m_iWeapon = W_NONE;
	m_iCurHP = m_iMaxHP = 15;
}

void CPlayer::LateInit()
{
}

OBJECT_STATE CPlayer::Update()
{
	if (!m_bIsActive)
	{
		//Dead();
		return PLAY;
	}

	if (m_eCurStance == DAMAGED)
		return PLAY;

	ProcessInput();
	
	Dash();
	Move();
	Jump();
	Attack();

	m_tInfo.fX += m_fVelocityX;

	return PLAY;
}

void CPlayer::LateUpdate()
{
	if (m_eCurStance == DAMAGED)
	{
		//Damaged();
	}

	FrameMove();
	UpdateRect();
	SceneChange();
	ScrollMove();
}

void CPlayer::Render(HDC hDC)
{
	DrawObjectScroll(hDC, m_pFrameKey);
}

void CPlayer::Release()
{
}

void CPlayer::ProcessInput()
{
	// 무기 변경
	if (KeyManager->KeyDown('a') || KeyManager->KeyDown('A'))
	{
		m_iWeapon++;
		if (m_iWeapon >= W_END)
			m_iWeapon -= W_END;
	}

	//무기 변경
	if (KeyManager->KeyDown('s') || KeyManager->KeyDown('S'))
	{
		m_iWeapon--;
		if (m_iWeapon < 0)
			m_iWeapon += W_END;
	}

	//기가 스킬
	if (KeyManager->KeyDown('f') || KeyManager->KeyDown('F'))
	{
		if (m_iArmor != A_NONE)
		{
			//노바스트라이크
		}
	}

	//일반 공격 1회
	if (KeyManager->KeyDown('c') || KeyManager->KeyDown('C') ||
		KeyManager->KeyDown('v') || KeyManager->KeyDown('V'))
	{

	}

	// Jump : 'X 'Pressing
	// 점프 중 일때 공격하면 JumpATT로 바뀜
	if (KeyManager->KeyPressing('x') || KeyManager->KeyPressing('X'))
	{

	}

	// Dash : 'Z' Pressing
	// 대시 중일때 점프하면 대시 X속도 값 기준으로 점프
	if (KeyManager->KeyPressing('z') || KeyManager->KeyPressing('Z'))
	{

	}

	// Weapon Charge Attack: 'C' Pressing
	// 웨폰 없을 시 기본 공격
	// 0.5초 유지 되면 하프 버스터 발사
	// 1초 유지 되면 풀 버스터 발사
	if (KeyManager->KeyPressing('c') || KeyManager->KeyPressing('C'))
	{

	}

	// Normal Charge ATTACK : 'V' Pressing
	// 0.5초 유지 되면 하프 버스터 발사
	// 1초 유지 되면 풀 버스터 발사
	if (KeyManager->KeyPressing('v') || KeyManager->KeyPressing('V'))
	{

	}

}

void CPlayer::Move()
{
	if (m_bDash && !m_bAttack)
	{
		m_fAccelX = 10.f;
		m_fSpeed = 5.f;

		if (!m_bJump && !m_bAttack)
			m_eCurStance = DASH;

		if (m_tFrame.iStart == m_tFrame.iEnd)
			m_tFrame.iStart = 1;
	}
	else if (m_bJump)
	{

	}

	// WALK : 좌우 방향키 Pressing 
	// 만일 Object와 충돌 중일때 Pressing이 유지되면 벽 매달리기

	if (KeyManager->KeyPressing(VK_LEFT))
	{
		m_bIsLeft = true;
		m_pFrameKey = m_pLeftFrameKey;
		if (m_bWall)
		{

		}
	}

	if (KeyManager->KeyPressing(VK_RIGHT))
	{
		m_bIsLeft = false;
		m_pFrameKey = m_pRightFrameKey;
	}
}

void CPlayer::Attack()
{
}

void CPlayer::Jump()
{
}

void CPlayer::Dash()
{
}

void CPlayer::FrameMove()
{
}

void CPlayer::SceneChange()
{
}

void CPlayer::ScrollMove()
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();

	if (BUFCX * 0.5f < m_tInfo.fX + fScrollX && m_fVelocityX > 0)
		GameManager->SetScrollX(fScrollX - m_fVelocityX);

	if (BUFCX * 0.5f > m_tInfo.fX + fScrollX && m_fVelocityX < 0)
		GameManager->SetScrollX(fScrollX - m_fVelocityX);
}
