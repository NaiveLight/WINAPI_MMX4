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

	static CGameObject* CreateObj(float fX, float fY, bool bIsLeft)
	{
		CGameObject* pObj = new T;
		pObj->Init();
		pObj->SetPos(fX, fY);
		pObj->SetIsLeft(bIsLeft);

		return pObj;
	}

	static CGameObject* CreateObj(float fX, float fY, TCHAR* pFrameKey)
	{
		CGameObject* pObj = new T;
		pObj->Init();
		pObj->SetPos(fX, fY);
		pObj->SetFrameKey(pFrameKey);

		return pObj;
	}

	static CGameObject* CreateObj(TCHAR* pFrameKey, int iEnd, int m_iFrameCnt, int iScene, int iSceneCnt)
	{
		CGameObject* pObj = new T;
		pObj->Init();
		pObj->SetFrameKey(pFrameKey);
		pObj->SetFrameEnd(iEnd);
		pObj->SetFrameCnt(m_iFrameCnt);
		pObj->SetFrameScene(iScene);
		pObj->SetSceneCnt(iSceneCnt);

		return pObj;
	}

	static CGameObject* CreateObj(float fX, float fY, TCHAR* pFrameKey, int iEnd, int m_iFrameCnt, int iScene, int iSceneCnt)
	{
		CGameObject* pObj = new T;
		pObj->Init();
		pObj->SetPos(fX, fY);
		pObj->SetFrameKey(pFrameKey);
		pObj->SetFrameEnd(iEnd);
		pObj->SetFrameCnt(m_iFrameCnt);
		pObj->SetFrameScene(iScene);
		pObj->SetSceneCnt(iSceneCnt);

		return pObj;
	}

	static CGameObject* CreateRectGround(RECT& rc)
	{
		CGameObject* pObj = new T(rc);
		pObj->Init();
		pObj->SetIsLeft(true);
		return pObj;
	}

	static CGameObject* CreateLineGround(POINT& p1, POINT& p2)
	{
		CGameObject* pObj = new T(p1, p2);
		pObj->Init();
		pObj->SetIsLeft(false);

		return pObj;
	}
};