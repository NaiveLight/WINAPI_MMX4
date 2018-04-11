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
	float m_fMinScrollX;
	float m_fMinScrollY;
	float m_fMaxScrollX;
	float m_fMaxScrollY;

	float m_fPrevScrollX;
	float m_fPrevScrollY;
	
	// 카메라 흔들기
	float m_fShakePower;
	DWORD m_dwShakeTime;
	
	bool m_bIsShaking;
	bool m_bIsPaused;
	bool m_bDebugMode;

	bool m_bHitboxDraw = false;

public:
	CGameManager();
	virtual ~CGameManager();

public:
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	//Getter
	CGameObject* GetPlayer() { return m_ObjectList[OBJ_PLAYER].back(); }
	CGameObject* GetTargetByFrameKey(const TCHAR* pFrameKey, OBJECT_ID eID);
	OBJLIST& GetObjList(OBJECT_ID eID) { return m_ObjectList[eID]; }
	RECT& GetScreen() { return m_tScreenRect; }

	float GetScrollX() { return m_fScrollX; }
	float GetScrollY() { return m_fScrollY; }
	float GetMaxScrollX() { return m_fMaxScrollX; }
	float GetMaxScrollY() { return m_fMaxScrollY; }

public:
	//Setter
	void SetScrollX(float fX);
	void SetScrollY(float fY); 
	void SetCurScrollX(float fX) { m_fScrollX = fX; }
	void SetCurScrollY(float fY) { m_fScrollY = fY; }
	void SetMaxScrollX(float fX) { m_fMaxScrollX = fX; }
	void SetMaxScrollY(float fY) { m_fMaxScrollY = fY; }
	void SetMinScrollX(float fX) { m_fMinScrollX = fX; }
	void SetMinScrollY(float fY) { m_fMinScrollY = fY; }
	void SetPause(bool bIsPaused) { m_bIsPaused = bIsPaused; }

public:
	void AddObject(CGameObject* pObj, OBJECT_ID eID);
	void ReleaseObj(OBJECT_ID eID);
	void ResetScroll()
	{
		m_fScrollX = m_fScrollY = m_fMaxScrollX = m_fMaxScrollY = 0;
	}

public:
	void SetCameraShaking(bool bIsShaking);
	void CameraShakingStart(float fPower);
	void CameraShakingStart(float fPower, DWORD dwShakeEndTime);
	void CameraShakingEnd();
};

