#pragma once
#include "GameObject.h"
class CGround :
	public CGameObject
{
	// isLeft = true -> Rect / false -> Line
public:
	CGround();

	CGround(RECT& rc)
		: m_ptLeftTop{}, m_ptRightBottom{}
	{
		m_tTexRect.left = rc.left;
		m_tTexRect.top = rc.top;
		m_tTexRect.right = rc.right;
		m_tTexRect.bottom = rc.bottom;

		m_bIsLeft = true;
	}

	CGround(POINT& ptLF, POINT& ptRB)
	{
		m_tTexRect = {};
		m_ptLeftTop = ptLF;
		m_ptRightBottom = ptRB;

		m_bIsLeft = false;
	}
	virtual ~CGround();

	// CGameObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void LateInit();
	virtual OBJECT_STATE Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;


public:
	POINT& GetPointLT() { return m_ptLeftTop; }
	POINT& GetPointRB() { return m_ptRightBottom; }

private:
	POINT m_ptLeftTop;
	POINT m_ptRightBottom;
};

