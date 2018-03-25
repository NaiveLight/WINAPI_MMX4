#pragma once

class CGameObject;
class CGameManager :
	public CSingleton<CGameManager>
{
private:
	OBJLIST m_ObjectList[OBJ_END];

	RECT m_tScreenRect;

	// ��ũ��
	float m_fScrollX;
	float m_fScrollY;
	float m_fMaxScrollX;
	float m_fMaxScrollY;
	
	// ī�޶� ����
	float m_fShakePower;
	DWORD m_dwShakeTime;
	
	bool m_bIsShaking;
	bool m_bIsPaused;
	bool m_bDebugMode;

public:
	CGameManager();
	virtual ~CGameManager();
};

