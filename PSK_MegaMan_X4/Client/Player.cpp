#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	:m_pLeftFrameKey(nullptr), m_pRightFrameKey(nullptr),
	m_eCurStance(ST_END), m_ePrevStance(ST_END),
	m_bWalk(false), m_bDash(false), m_bJump(false), m_bAttack(false), m_bCharge(false),
	m_bGround(false), m_bWall(false), m_bDamaged(false),
	m_fAccelX(0.f), m_fAccelY(0.f)
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
	m_iHitBoxCX = 30;
	m_iHitBoxCY = 45;

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
	m_iCurHP = m_iMaxHP = 15;

	m_fSpeedX = 2.f;
	m_fSpeedY = -4.5f;
	m_fVelocityX = 0.f;
	m_fVelocityY = 8.f;
	m_fJumpSpeed = -5.5f;
	m_fJumpAccel = 0.25f;
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

	if (m_eCurStance == SPAWN)
	{
		m_tInfo.fY += m_fVelocityY;
		return PLAY;
	}

	if (m_eCurStance == DAMAGE_HIGH || m_eCurStance == DAMAGE_LOW)
		return PLAY;
	


	if (!m_bJump)
	{
		Walk();

		m_fVelocityX = m_fAccelX;

		if (KeyManager->KeyPressing('X'))
		{
			m_bJump = true;
			m_fVelocityY = m_fJumpSpeed;
		}
	}
	else
	{
		m_fVelocityY += m_fJumpAccel;

		if (m_bGround && m_bWall)
			m_bJump = false;

		if (KeyManager->KeyUp('X') && m_fVelocityY < 0)
			m_fVelocityY *= -1;
			
	}

	if (m_bJump)
	{
		m_eCurStance = JUMP;
	}

	if (!m_bWalk && !m_bJump)
	{
		m_eCurStance = IDLE;
	}
	

	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY += m_fVelocityY;


	return PLAY;
}

void CPlayer::LateUpdate()
{
	if (m_eCurStance == DAMAGE_HIGH || m_eCurStance == DAMAGE_LOW)
	{
		//Damaged();
	}

	UpdateRect();

	//system("cls");
	//cout << "INFO\n";
	//cout << m_tInfo.fX << endl;
	//cout << m_tInfo.fY << endl;

	//cout << "TEXBOX\n";
	//cout << m_tTexRect.left << endl;
	//cout << m_tTexRect.right << endl;

	//cout << "HITBOX\n";
	//cout << m_tHitBoxRect.left << endl;
	//cout << m_tHitBoxRect.right << endl;

	//cout << "SCrollX\n";
	//cout << GameManager->GetScrollX() << endl;


	m_bGround = CCollision::PlayerGround(this, GameManager->GetObjList(OBJ_GROUND));

	//if (!m_bGround && !m_bWall)
	//{
	//	m_eCurStance =JUMP;
	//	m_bJump = false;
	//}

	SceneChange();
	FrameMove();
	ScrollMove();
}

void CPlayer::Render(HDC hDC)
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();
	DrawHitBox(hDC);
	//Rectangle(hDC, m_tHitBoxRect.left - fScrollX, m_tHitBoxRect.top, m_tHitBoxRect.right - fScrollX, m_tHitBoxRect.bottom);
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

	m_tHitBoxRect.left = LONG(m_tInfo.fX - m_iHitBoxCX / 2 /*- fScrollX*/);
	m_tHitBoxRect.top = LONG(m_tInfo.fY - m_iHitBoxCY / 2 /*- fScrollY*/);
	m_tHitBoxRect.right = LONG(m_tInfo.fX + m_iHitBoxCX / 2 /*- fScrollX + 5*/);
	m_tHitBoxRect.bottom = LONG(m_tInfo.fY + m_iHitBoxCY / 2 /*- fScrollY*/);
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
		case GROUND:
			if (!m_bGround)
				return;
			break;
		}

		++m_tFrame.iStart;

		m_tFrame.dwTime = GetTickCount();
	}

	// 각 상황마다 다르게 처리 해주어야한다.
	if (m_tFrame.iStart > m_tFrame.iEnd)
	{
		switch (m_tFrame.iScene)
		{
		//SPAWN은 끝나면 IDLE상태로 변환 되어야 한다.
		case SPAWN:
			m_eCurStance = IDLE;
			break;
		case IDLE:
			m_tFrame.iStart = 0;
			break;
		case WALK:
			m_tFrame.iStart = 2;
			break;
		case JUMP:
			m_tFrame.iStart = m_tFrame.iEnd;
			break;
		case GROUND:
			m_eCurStance = IDLE;
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
		m_tFrame.dwSpeed = 250;
		break;
	case WALK:
		m_tFrame.iScene = 4;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;
	case JUMP:
		m_tFrame.iScene = 6;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 7;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
		break;
	case GROUND:
		m_tFrame.iScene = 8;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 100;
		break;
	}
}

void CPlayer::NoArmorRFScene()
{
	m_pLeftFrameKey = L"X_LEFT";
	m_pRightFrameKey = L"X_RIGHT";
	m_pFrameKey = m_bIsLeft ? m_pLeftFrameKey : m_pRightFrameKey;

	switch (m_eCurStance)
	{

	}
}

void CPlayer::UltiNoWeaponScene()
{
}

void CPlayer::UltiRFScene()
{
}

void CPlayer::Walk()
{
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
		m_fAccelX = 0;
	}

	if (m_bIsLeft && m_bWalk)
		m_fAccelX *= -1;

	if (m_bWalk)
		m_eCurStance = WALK;
}
