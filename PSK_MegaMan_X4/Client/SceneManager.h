#pragma once
#include "Scene.h"

class CSceneManager :
	public CSingleton<CSceneManager>
{
public:
	enum SCENEID {TITLE, MENU, PLAYERSELECT, LOBBY, STAGE, SCENE_END};
private:
	CScene* m_pCurScene;
	SCENEID m_eCurScene;
	SCENEID m_ePrevScene;

	bool m_bIsFade;
	BYTE m_btAlpha;

public:
	CSceneManager();
	~CSceneManager();

public:
	void LateInit();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	void FadeIn();
	void FadeOut();
	void ChangeScene(SCENEID eSceneID);
	void RestartScene();
};

