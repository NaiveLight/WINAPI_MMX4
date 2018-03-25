#pragma once
class CGameObject
{
protected:
	INFO m_tInfo;			// 위치
	RECT m_tTexRect;		// 그림이 그려질 렉트
	RECT m_tHitBoxRect;		// 충돌 렉트
	int m_iHitBoxCX;		// 충돌렉트 x 사이즈
	int m_iHitBoxCY;		// 충돌렉트 y 사이즈

	FRAME m_tFrame;			// 비트맵(애니메이션) 프레임 정보
	TCHAR* m_pFrameKey;		// 가져올 비트맵의 키값
	CGameObject* m_pTarget;	// 대상으로 하는 오브젝트

	bool m_bIsInit;			// LateInit이 실행 되었는가
	bool m_bIsActive;		// 활성화 되어있는가
	bool m_bIsLeft;			// 왼쪽을 바라보는가 오른쪽을 바라보는가

	int m_iAttack;			// 공격력

	float m_fSpeed;			// 속도

public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual void Init() = 0;
	virtual void LateInit();
	virtual OBJECT_STATE Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	void UpdateRect();
	void UpdateRect(float fX, float fY);
	void FrameMove();
	void DrawObject(HDC hDC, const TCHAR* szName);
	void DrawHitBox(HDC hDC);

public:
	//Getter 
	const INFO& GetInfo()			{ return m_tInfo; }
	const RECT& GetTexRect()		{ return m_tTexRect; }
	const RECT& GetHitBoxRect()		{ return m_tHitBoxRect; }
	const bool& GetIsActive()		{ return m_bIsActive; }
	const bool& GetIsLeft()			{ return m_bIsLeft; }
	const int& GetHitBoxCX()		{ return m_iHitBoxCX; }
	const int& GetHitBoxCY()		{ return m_iHitBoxCY; }
	const int& GetAttack()			{ return m_iAttack; }
	const float& GetSpeed()			{ return m_fSpeed; }

public:
	//Setter
	void SetPos(float& fX, float& fY)	{}
	void SetHitBox(int& iCX, int& iCY)	{}
	void SetActive() {}
	void SetTarget(CGameObject* pTarget) { m_pTarget = pTarget; }
};

