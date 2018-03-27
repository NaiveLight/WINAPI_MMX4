#pragma once
class CGameObject
{
protected:
	INFO m_tInfo;			// ��ġ
	RECT m_tTexRect;		// �׸��� �׷��� ��Ʈ
	RECT m_tHitBoxRect;		// �浹 ��Ʈ
	int m_iHitBoxCX;		// �浹��Ʈ x ������
	int m_iHitBoxCY;		// �浹��Ʈ y ������

	FRAME m_tFrame;			// ��Ʈ��(�ִϸ��̼�) ������ ����
	TCHAR* m_pFrameKey;		// ������ ��Ʈ���� Ű��
	CGameObject* m_pTarget;	// ������� �ϴ� ������Ʈ

	bool m_bIsInit;			// LateInit�� ���� �Ǿ��°�
	bool m_bIsActive;		// Ȱ��ȭ �Ǿ��ִ°�
	bool m_bIsLeft;			// ������ �ٶ󺸴°� �������� �ٶ󺸴°�

	int m_iAttack;			// ���ݷ�
	float m_fSpeed;			// �ӵ�
	int m_iDrawID;

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
	//void UpdateRect(float fX, float fY);
	void FrameMove();
	void DrawObject(HDC hDC, const TCHAR* szName);
	void DrawHitBox(HDC hDC);

public:
	//Getter 
	const INFO& GetInfo()			{ return m_tInfo; }
	const RECT& GetTexRect()		{ return m_tTexRect; }
	const RECT& GetHitBoxRect()		{ return m_tHitBoxRect; }
	const TCHAR* GetFrameKey() { return m_pFrameKey; }
	const bool& GetIsActive()		{ return m_bIsActive; }
	const bool& GetIsLeft()			{ return m_bIsLeft; }
	const int& GetHitBoxCX()		{ return m_iHitBoxCX; }
	const int& GetHitBoxCY()		{ return m_iHitBoxCY; }
	const int& GetAttack()			{ return m_iAttack; }
	const float& GetSpeed()			{ return m_fSpeed; }

public:
	//Setter
	void SetPos(float& fX, float& fY)		{ m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetHitBox(int& iCX, int& iCY)		{ m_iHitBoxCX = iCX; m_iHitBoxCY = iCY; }
	void SetActive(bool bIsActive)			{ m_bIsActive = bIsActive; }
	void SetIsLeft(bool bIsLeft)			{ m_bIsLeft = bIsLeft; }
	void SetTarget(CGameObject* pTarget)	{ m_pTarget = pTarget; }
	void SetFrameKey(TCHAR* pFrameKey)		{ m_pFrameKey = pFrameKey; }
	void SetDrawID(int iDrawID)				{ m_iDrawID = iDrawID; }

	void IncreaseDrawID() { m_iDrawID++;}
	void DecreaseDrawID() { m_iDrawID--; }
};

