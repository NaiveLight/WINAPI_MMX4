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
	m_tInfo.fX = 150.f;
	m_tInfo.fY = 170.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_iHitBoxCX = 30;
	m_iHitBoxCY = 45;

	m_pLeftFrameKey = L"X_LEFT";
	m_pFrameKey = m_pRightFrameKey = L"X_RIGHT"; 

	SetStartPos(m_tInfo.fX, m_tInfo.fY);

	m_bIsActive = true;
	m_bIsLeft = false;
	m_iFrameCnt = 17;
	m_iSceneCnt = 24;
	m_tFrame.iScene = 1;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 4;
	m_tFrame.dwSpeed = 150;
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
	CGameObject::LateInit();

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
	m_fVelocityX = 0;

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
	int iScrollX = (int)GameManager->GetScrollX();
	int iScrollY = (int)GameManager->GetScrollY();

	CMyBmp* pBmp = BmpManager->FindImage(m_pFrameKey);

	int iSizeX = pBmp->GetBmpCX() / (m_iFrameCnt);
	int iSizeY = pBmp->GetBmpCY() / (m_iSceneCnt);

	DrawHitBox(hDC);
	GdiTransparentBlt(hDC, m_tTexRect.left - iScrollX, m_tTexRect.top - iScrollY, (int)m_tInfo.fCX, (int)m_tInfo.fCY, pBmp->GetMemDC(),
		m_tFrame.iStart * iSizeX, m_tFrame.iScene * iSizeY, iSizeX, iSizeY, RGB(255, 0, 255));
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

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2 - fScrollX);
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2 - fScrollY);
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2 - fScrollX + 5);
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2 - fScrollY);
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
	m_fMaxSpeed = 2.f;
	m_fAccelX = 1.f;
	// WALK : 좌우 방향키 Pressing 
	// 만일 Object와 충돌 중일때 Pressing이 유지되면 벽 매달리기

	if (KeyManager->KeyPressing(VK_LEFT))
	{
		m_bIsLeft = true;
		m_pFrameKey = m_pLeftFrameKey;
		m_tFrame.iScene = 6;
		m_tFrame.iEnd = 15;

		m_fVelocityX -= m_fMaxSpeed;
	}

	if (KeyManager->KeyPressing(VK_RIGHT))
	{
		m_bIsLeft = false;
		m_pFrameKey = m_pRightFrameKey;
		m_fVelocityX += m_fMaxSpeed;
		m_tFrame.iScene = 6;
		m_tFrame.iEnd = 15;
	}

	if (m_fVelocityX > m_fMaxSpeed && m_fVelocityX > 0)
		m_fVelocityX = m_fMaxSpeed;
	else if (m_fVelocityX < -m_fMaxSpeed && m_fVelocityX < 0)
		m_fVelocityX = -m_fMaxSpeed;
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

void CPlayer::SceneChange()
{
	if (m_ePrevStance != m_eCurStance)
	{

	}
}

void CPlayer::ScrollMove()
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();

	if (BUFCX * 0.6f  < m_tInfo.fX - fScrollX)
		GameManager->SetScrollX(m_fMaxSpeed);

	if (BUFCX * 0.4f > m_tInfo.fX - fScrollX)
		GameManager->SetScrollX(-m_fMaxSpeed);
}
