#pragma once
#include "GameObject.h"
class CLBText :
	public CGameObject
{
public:
	CLBText();
	virtual ~CLBText();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void LateInit() override;
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void IncreaseFrameStart() 
	{ 
		m_tFrame.iStart++; 	
		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = m_tFrame.iEnd;
	}
	const int& GetFrameStart() { return m_tFrame.iStart; }
};

