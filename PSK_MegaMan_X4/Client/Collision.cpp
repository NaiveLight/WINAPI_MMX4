#include "stdafx.h"
#include "Collision.h"
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"

CCollision::CCollision()
{
}


CCollision::~CCollision()
{
}

bool CCollision::Screen(RECT & tScreen, CGameObject * pObj)
{
	RECT rc = {};

	if (IntersectRect(&rc, &tScreen, &pObj->GetTexRect()))
		return true;

	return false;
}

bool CCollision::PlayerGround(CPlayer* pPlayer, OBJLIST & srcList)
{
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
			if (IntersectRect(&rc, &(pPlayer->GetHitBoxRect()), &(pSrc->GetTexRect())))
			{
				fMoveX = float(rc.right - rc.left);
				fMoveY = float(rc.bottom - rc.top);

				if (fMoveX < fMoveY)
				{
					if (pPlayer->GetHitBoxRect().left < pSrc->GetTexRect().left)
						fMoveX *= -1.f;

					pPlayer->SetPos(pPlayer->GetInfo().fX + fMoveX , pPlayer->GetInfo().fY);
					pPlayer->SetVelocityX(0.f);
					pPlayer->SetVelocityY(0.f);

					return false;
				}
				else
				{
					if (pPlayer->GetInfo().fY + pPlayer->GetHitBoxCY() * 0.5f > pSrc->GetTexRect().bottom)
					{
						pPlayer->SetPos(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY + fMoveY);
						
						return false;
					}
					else
					{
						float x1 = float(pSrc->GetTexRect().left);
						float x2 = float(pSrc->GetTexRect().right);
						float y = float(pSrc->GetTexRect().top);

						float fGradient = (y - y) / (x2 - x1);
						fMoveY = fGradient * (pPlayer->GetInfo().fX - x1) + y;
						pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
						pPlayer->SetVelocityY(0);

						return true;
					}
					
				}
				
			}
		}
		else
		{
			// 라인 Ground 충돌
			float x1 = (float)dynamic_cast<CGround*>(pSrc)->GetPointLT().x;
			float x2 = (float)dynamic_cast<CGround*>(pSrc)->GetPointRB().x;

			float fScrollX = GameManager->GetScrollX();

			if (x1 < pPlayer->GetInfo().fX && pPlayer->GetInfo().fX < x2)
			{
				float y1 = (float)dynamic_cast<CGround*>(pSrc)->GetPointLT().y;
				float y2 = (float)dynamic_cast<CGround*>(pSrc)->GetPointRB().y;

				float fGradient = (y2 - y1) / (x2 - x1);
				fMoveY = fGradient * (pPlayer->GetInfo().fX - x1) + y1;

				if (fMoveY - pPlayer->GetHitBoxCY() * 0.55f >= pPlayer->GetInfo().fY)
					return false;

				pPlayer->SetPos(pPlayer->GetInfo().fX, fMoveY - pPlayer->GetHitBoxCY() * 0.45f);
				pPlayer->SetVelocityY(0.f);
				return true;
			}
		}
	} // for

	return false;
}
