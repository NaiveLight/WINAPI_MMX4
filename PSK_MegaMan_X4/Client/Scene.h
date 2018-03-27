#pragma once
class CScene
{
private:
	bool m_bIsInit;

public:
	CScene();
	virtual ~CScene();

public:
	virtual void Init() = 0;
	virtual void LateInit();
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

protected:
	void DrawBackground(HDC hDC, const TCHAR* szName);
	void DrawBackground(HDC hDC, const TCHAR* szName, float fScrollX, float fScrollY);
};

