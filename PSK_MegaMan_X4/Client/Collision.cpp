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

//벽 충돌 처리
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
						//cout << "벽 좌측 충돌\n";
						fMoveX *= -1.f;
						isWallLeft = true;
					}

					if (pPlayer->GetIsGround())
					{
						pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX, pPlayer->GetInfo().fY);

					}
				}
			}  // 렉트 충돌시 
		}
	}
	return false;
}

//바닥 천정 충돌 처리
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
			// 라인 Ground 충돌
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
						//cout << "아무곳도 충돌 안했을 경우\n";
						pPlayer->SetAccelY(2.5f);
						pPlayer->SetJump(true);
						pPlayer->SetWall(false);
					}
					return false;
				}


				pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
				pPlayer->SetVelocityY(0.f);
				pPlayer->SetAccelY(0.f);
				//cout << "라인 위 충돌\n";
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
					//위 아래 판별
					if (pPlayer->GetInfo().fY + pPlayer->GetHitBoxCY() * 0.5f > pSrc->GetHitBoxRect().bottom)
					{
						//cout << "렉트 하단 충돌\n";
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
							//cout << "렉트 상단에서 떨어질때\n";
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
							//cout << "땅 + 벽 좌측 충돌\n";
							fMoveX *= -1.f;
						}
						else
						{
							//cout << "땅 + 벽 우측 충돌\n";
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
								//cout << "땅 + 벽 좌측 충돌\n";
								fMoveX *= -1.f;
							}
							//cout << "렉트 좌우 떨어질때\n";
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
								//cout << "벽 좌측 충돌\n";
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
								//cout << "벽 우측 충돌\n";
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
		}  // 렉트 충돌시 
	}
}

void CCollision::BulletToObject(OBJLIST & bulletList, OBJLIST & srcList)
{

}
