#pragma once

// �߻� ���丮 ����
// ��ü ���� ���� ������ ����

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