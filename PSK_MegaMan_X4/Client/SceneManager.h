#pragma once
#include "Scene.h"

class CSceneManager :
	public CSingleton<CSceneManager>
{
public:
	enum SCENEID {TITLE, MENU, PLAYERSELECT, LOBBY, STAGE1_1, STAGE1_2, SCENE_END};
private:
	CScene* m_pCurScene;
	SCENEID m_eCurScene;
	SCENEID m_ePrevScene;

	bool m_bIsFade;
	int m_btAlpha;

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
	bool FadeIn();
	bool FadeOut();
	void DrawAlphaColor(HDC hDC, int Alpha);
	void ChangeScene(SCENEID eSceneID);
	void RestartScene()
	{
		m_ePrevScene = SCENE_END; 
		ChangeScene(m_eCurScene);
	}
};

