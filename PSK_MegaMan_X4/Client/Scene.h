#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
};

