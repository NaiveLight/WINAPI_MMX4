#pragma once

class CGameObject;
class CGameManager :
	public CSingleton<CGameManager>
{
private:
	OBJLIST m_ObjectList[OBJ_END];

	RECT m_tScreenRect;

	// 스크롤
	float m_fScrollX;
	float m_fScrollY;
	float m_fMaxScrollX;
	float m_fMaxScrollY;
	
	// 카메라 흔들기
	float m_fShakePower;
	DWORD m_dwShakeTime;
	
	bool m_bIsShaking;
	bool m_bIsPaused;
	bool m_bDebugMode;

public:
	CGameManager();
	virtual ~CGameManager();
};

