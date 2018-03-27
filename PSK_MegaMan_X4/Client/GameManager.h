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
	void SetScrollX(float fX) { m_fScrollX = fX; }
	void SetScrollY(float fY) { m_fScrollY = fY; }
	void SetMaxScrollX(float fX) { m_fMaxScrollX = fX; }
	void SetMaxScrollY(float fY) { m_fMaxScrollY = fY; }
	void SetPause(bool bIsPaused) { m_bIsPaused = bIsPaused; }

public:
	void AddObject(CGameObject* pObj, OBJECT_ID eID);
	void ReleaseObj(OBJECT_ID eID);

public:
	void SetCameraShaking(bool bIsShaking);
};

