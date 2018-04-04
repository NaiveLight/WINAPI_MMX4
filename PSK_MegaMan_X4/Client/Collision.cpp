#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "Bullet.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

bool CCollision::Screen(RECT & tScreen, CGameObject * pObj)
{
	RECT rc = {};

	if (IntersectRect(&rc, &tScreen, &pObj->GetHitBoxRect()))
		return true;

	return false;
}

//�� �浹 ó��
bool CCollision::PlayerToWall(CPlayer * pPlayer, OBJLIST & srcList)
{
	if (pPlayer->GetIsGround())
		return false;

	if (!pPlayer->GetIsActive())
	{
		return false;
	}

	float fMoveX = 0.f;
	float fMoveY = 0.f;

	for (auto& pSrc : srcList)
	{
		// true = RECT, false = Line
		if (pSrc->GetIsLeft())
		{
			RECT rc = {};
			if (IntersectRect(&rc, &(pPlayer->GetHitBoxRect()), &(pSrc->GetHitBoxRect())))
			{
				fMoveX = float(rc.right - rc.left);
				fMoveY = float(rc.bottom - rc.top);

				if (fMoveX < fMoveY)
				{
					bool isWallLeft = false;
					if (pPlayer->GetHitBoxRect().left < pSrc->GetHitBoxRect().left)
					{
						//cout << "�� ���� �浹\n";
						fMoveX *= -1.f;
						isWallLeft = true;
					}

					if (pPlayer->GetIsGround())
					{
						pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);

					}
				}
			}  // ��Ʈ �浹�� 
		}
	}
	return false;
}

//�ٴ� õ�� �浹 ó��
bool CCollision::PlayerToGround(CPlayer * pPlayer, OBJLIST & srcList)
{
	if (!pPlayer->GetIsActive())
	{
		return false;
	}

	float fMoveX = 0.f;
	float fMoveY = 0.f;

	//bool bGround = false;`

	for (auto& pSrc : srcList)
	{
		// true = RECT, false = Line
		if (!pSrc->GetIsLeft())
		{
			// ���� Ground �浹
			float x1 = (float)dynamic_cast<CGround*>(pSrc)->GetPointLT().x;
			float x2 = (float)dynamic_cast<CGround*>(pSrc)->GetPointRB().x;

			if (x1 < pPlayer->GetInfo().fX && pPlayer->GetInfo().fX < x2)
			{

				float y1 = (float)dynamic_cast<CGround*>(pSrc)->GetPointLT().y;
				float y2 = (float)dynamic_cast<CGround*>(pSrc)->GetPointRB().y;

				float fGradient = (y2 - y1) / (x2 - x1);
				fMoveY = fGradient * (pPlayer->GetInfo().fX - x1) + y1;

				if (fMoveY - pPlayer->GetHitBoxCY() * 0.55f >= pPlayer->GetInfo().fY)
				{
					if (pPlayer->GetWall())
					{
						//cout << "�ƹ����� �浹 ������ ���\n";
						pPlayer->SetAccelY(2.5f);
						pPlayer->SetJump(true);
						pPlayer->SetWall(false);
					}
					return false;
				}


				pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
				pPlayer->SetVelocityY(0.f);
				pPlayer->SetAccelY(0.f);
				//cout << "���� �� �浹\n";
				return true;
			}
		}
		else
		{
			RECT rc = {};
			if (IntersectRect(&rc, &(pPlayer->GetHitBoxRect()), &(pSrc->GetHitBoxRect())))
			{
				fMoveX = float(rc.right - rc.left);
				fMoveY = float(rc.bottom - rc.top);

				if (fMoveX > fMoveY)
				{
					//�� �Ʒ� �Ǻ�
					if (pPlayer->GetInfo().fY + pPlayer->GetHitBoxCY() * 0.5f > pSrc->GetHitBoxRect().bottom)
					{
						//cout << "��Ʈ �ϴ� �浹\n";
						pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY + fMoveY);
						pPlayer->SetVelocityY(0.f);
						return false;
					}
					else
					{
						float x1 = float(pSrc->GetHitBoxRect().left);
						float x2 = float(pSrc->GetHitBoxRect().right);

						if (x1 > pPlayer->GetInfo().fX|| x2 < pPlayer->GetInfo().fX)
						{
							//cout << "��Ʈ ��ܿ��� ��������\n";
							pPlayer->SetAccelX(1.5f);
							pPlayer->SetAccelY(2.5f);
							pPlayer->SetWall(false);
							pPlayer->SetJump(true);
							//pPlayer->SetStance(CPlayer::JUMP);
							//pPlayer->SetFrameScene(6);
							//pPlayer->SetFrameStart(6);
							return false;
						}

						float y = float(pSrc->GetHitBoxRect().top);
						float fGradient = (y - y) / (x2 - x1);
						fMoveY = fGradient * (pPlayer->GetInfo().fX - x1) + y;

						pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
						pPlayer->SetAccelX(0.f);
						pPlayer->SetVelocityY(0.f);
						pPlayer->SetJump(false);
						return true;
					}
				}
				else
				{
					if (pPlayer->GetIsGround())
					{
						if (pPlayer->GetHitBoxRect().left < pSrc->GetHitBoxRect().left)
						{
							//cout << "�� + �� ���� �浹\n";
							fMoveX *= -1.f;
						}
						else
						{
							//cout << "�� + �� ���� �浹\n";
						}
						pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);
						pPlayer->SetWall(false);
						pPlayer->SetJump(false);
					}
					else
					{
						float y1 = float(pSrc->GetHitBoxRect().top);
						float y2 = float(pSrc->GetHitBoxRect().bottom);

						if (y2 < pPlayer->GetInfo().fY - pPlayer->GetHitBoxCY() * 0.1f)
						{
							if (pPlayer->GetHitBoxRect().left < pSrc->GetHitBoxRect().left)
							{
								//cout << "�� + �� ���� �浹\n";
								fMoveX *= -1.f;
							}
							//cout << "��Ʈ �¿� ��������\n";
							pPlayer->SetAccelX(0.f);
							pPlayer->SetAccelY(2.5f);
							pPlayer->SetJump(true);
							pPlayer->SetWall(false);
							pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);
						}

						else if (pPlayer->GetHitBoxRect().left < pSrc->GetHitBoxRect().left)
						{
							if (KeyManager->KeyPressing(VK_RIGHT))
							{
								//cout << "�� ���� �浹\n";
								fMoveX *= -1.f;
								pPlayer->SetJump(false);
								pPlayer->SetWall(true);
								pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);
								pPlayer->SetAccelX(0.f);
								pPlayer->SetVelocityY(0.1f);
								pPlayer->SetAccelY(1.0f);
							}
							else
							{
								pPlayer->SetJump(true);
								pPlayer->SetVelocityY(2.5f);
								pPlayer->SetAccelY(2.5f);
							}
						}
						else
						{
							if (KeyManager->KeyPressing(VK_LEFT))
							{
								//cout << "�� ���� �浹\n";
								pPlayer->SetJump(false);
								pPlayer->SetWall(true);
								pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);
								pPlayer->SetAccelX(0.f);
								pPlayer->SetVelocityY(0.1f);
								pPlayer->SetAccelY(1.0f);
							}
							else
							{
								pPlayer->SetJump(true);
								pPlayer->SetVelocityY(2.5f);
								pPlayer->SetAccelY(2.5f);
							}
						}
						return false;
					}
				}
			}
		}  // ��Ʈ �浹�� 
	}
}

void CCollision::BulletToObject(OBJLIST & bulletList, OBJLIST & srcList)
{

}
