#pragma once

class CSceneManager :
	public CSingleton<CSceneManager>
{
public:
	CSceneManager();
	~CSceneManager();

public:
	void Init();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
};

