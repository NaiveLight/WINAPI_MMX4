#pragma once

// 추상 팩토리 패턴
// 객체 생성 관련 디자인 패턴

class CGameObject;

template<typename T>
class CAbstractFactory
{
public:
	static CGameObject* CreateObj()
	{
		CGameObject* pObj = new T;
		pObj->Init();

		return pObj;
	}

	static CGameObject* CreateObj(float fX, float fY)
	{
		CGameObject* pObj = new T;
		pObj->Init();
		pObj->SetPos(fX, fY);

		return pObj;
	}

	static CGameObject* CreateObj(float fX, float fY, bool bIsFlip)
	{
		CGameObject* pObj = new T;
		pObj->Init();
		pObj->SetPos(fX, fY);
		pObj->SetIsFlip(bIsFlip)

		return pObj;
	}

};